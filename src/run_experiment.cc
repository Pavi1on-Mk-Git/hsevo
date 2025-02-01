#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/array.hpp>
#include <filesystem>
#include <format>
#include <fstream>
#include <thread>

#include "ai/NEAT.h"
#include "ai/SimpleEvo.h"
#include "ai/evo_functions.hpp"
#include "logic/decklists.h"
#include "players/RandomPlayerLogic.h"
#include "utils/Rng.h"

static const unsigned SEED_COUNT = 30;
static const unsigned ITERATIONS = 500;
static const std::array<Decklist, DECK_COUNT> decklists = get_decklists();

std::ostream& operator<<(std::ostream& out, const std::vector<double>& vec)
{
    for(const auto& val: vec)
        out << val << "_";
    return out;
}

template <typename Algo, typename Evo, typename Config>
void single_seed_experiment(
    unsigned seed, const std::array<Config, DECK_COUNT>& configs, std::mutex& data_mutex,
    std::vector<std::ofstream>& result_files, std::array<std::vector<Evo>, DECK_COUNT>& best_specimen
)
{
    Rng rng(seed);

    std::vector<Algo> populations;
    std::ranges::transform(configs, std::back_inserter(populations), [&](const Config& config) {
        return Algo(config, rng);
    });

    std::array<std::vector<Evo>, DECK_COUNT> hall_of_champions;
    std::array<unsigned, DECK_COUNT> champion_scores;
    std::array<std::vector<unsigned>, DECK_COUNT> score_history;
    for(auto& score_vec: score_history)
        score_vec.reserve(ITERATIONS);

    for(unsigned iteration = 0; iteration < ITERATIONS; ++iteration)
    {
        std::array<std::vector<Evo>, DECK_COUNT> iteration_specimen;
        std::ranges::transform(populations, iteration_specimen.begin(), [](const Algo& algorithm) {
            return algorithm.get_population();
        });
        std::array<std::optional<std::pair<Evo, unsigned>>, DECK_COUNT> iteration_bests;

        auto iteration_scores = score_populations<Evo, DECK_COUNT>(iteration_specimen, decklists, rng);

        for(auto [best, population, new_scores, champions, decklist, champion_score, score_vec]: std::views::zip(
                iteration_bests, populations, iteration_scores, hall_of_champions, decklists, champion_scores,
                score_history
            ))
        {
            best = population.assign_scores(new_scores);

            auto contender_score = score_hall_of_champions(champions, best->first, decklist, rng);

            if(contender_score > champions.size() / 2)
            {
                champions.push_back(best->first);
                champion_score = best->second;
            }

            score_vec.push_back(champion_score);
            population.epoch();
        }
    }

    const std::lock_guard lock(data_mutex);

    for(auto [specimen_vec, champions]: std::views::zip(best_specimen, hall_of_champions))
        specimen_vec.push_back(champions.back());

    for(auto [result_file, scores]: std::views::zip(result_files, score_history))
    {
        std::ranges::copy(scores, std::ostream_iterator<unsigned>(result_file, ","));
        result_file << '\n';
    }
}

const unsigned COMPARISON_SEED = 42;

template <typename Algo, typename Evo, typename Config>
void experiment(const std::array<Config, DECK_COUNT>& configs)
{
    std::array<std::string, DECK_COUNT> file_suffixes;
    std::ranges::transform(configs, file_suffixes.begin(), [](const Config& config) { return config.name(); });

    for(auto [decklist, suffix]: std::views::zip(decklists, file_suffixes))
        if(std::filesystem::exists(
               std::filesystem::path(std::format("results/specimen/{}_{}.txt", decklist.name, suffix))
           ))
            return;

    std::mutex data_mutex;

    std::vector<std::ofstream> result_files;
    for(auto [decklist, suffix]: std::views::zip(decklists, file_suffixes))
        result_files.push_back(std::ofstream(std::format("results/scores/{}_{}", decklist.name, suffix)));

    std::array<std::vector<Evo>, DECK_COUNT> best_specimen;
    for(auto& specimen_vec: best_specimen)
        specimen_vec.reserve(SEED_COUNT);

    {
        std::vector<std::jthread> threads;

        for(unsigned seed = 0; seed < SEED_COUNT; ++seed)
            threads.push_back(std::jthread([&, seed]() {
                single_seed_experiment<Algo, Evo, Config>(seed, configs, data_mutex, result_files, best_specimen);
            }));
    }

    Rng rng(COMPARISON_SEED);

    auto final_scores = score_populations<Evo, DECK_COUNT>(best_specimen, decklists, rng);

    for(auto [bests, deck_final_scores, decklist, suffix]:
        std::views::zip(best_specimen, final_scores, decklists, file_suffixes))
    {
        auto the_best = bests.at(std::ranges::max_element(deck_final_scores) - deck_final_scores.begin());

        std::ofstream out(std::format("results/specimen/{}_{}.txt", decklist.name, suffix));
        the_best.save(out);
    }
}

template <typename Evo>
void score_once(
    unsigned seed, const std::array<std::vector<Evo>, DECK_COUNT>& populations,
    std::array<std::vector<unsigned>, DECK_COUNT>& total_scores, std::ofstream& comp_result_file,
    std::mutex& score_mutex
)
{
    Rng rng(seed);

    auto current_scores = score_populations<Evo, DECK_COUNT>(populations, decklists, rng);

    std::lock_guard lock(score_mutex);

    for(auto [total_score_vec, current_score_vec]: std::views::zip(total_scores, current_scores))
    {
        for(auto [total, current]: std::views::zip(total_score_vec, current_score_vec))
        {
            total += current;
            comp_result_file << current << ",";
        }
    }
    comp_result_file << "\n";
};

template <typename Algo, typename Evo, typename Config, typename Param>
void run_experiment(
    std::array<Config, DECK_COUNT>& configs, const std::vector<Param>& parameters,
    const std::function<void(Config&, const Param&)>& param_setter, const std::string& output_file_name,
    const std::optional<std::pair<std::string, std::function<void(Config&, boost::archive::text_iarchive&)>>>&
        input_data = std::nullopt
)
{
    if(input_data)
    {
        auto [name, config_loader] = *input_data;

        std::ifstream in("results/" + name + ".txt");
        boost::archive::text_iarchive iarchive(in);

        for(auto& config: configs)
            config_loader(config, iarchive);
    }

    std::array<std::vector<Evo>, DECK_COUNT> populations;

    for(const auto& param: parameters)
    {
        auto changed_configs = configs;
        for(auto& changed_config: changed_configs)
            param_setter(changed_config, param);

        experiment<Algo, Evo, Config>(changed_configs);

        std::vector<Evo> results;
        for(auto [decklist, config]: std::views::zip(decklists, changed_configs))
        {
            std::ifstream in(std::format("results/specimen/{}_{}.txt", decklist.name, config.name()));
            results.emplace_back(in);
        }

        for(auto [result, population]: std::views::zip(results, populations))
            population.push_back(result);
    }

    std::mutex score_mutex;
    std::array<std::vector<unsigned>, DECK_COUNT> total_scores;

    std::ofstream comp_result_file("results/comparisons/" + output_file_name + ".csv");

    for(const auto& decklist: decklists)
        for(const auto& param: parameters)
            comp_result_file << decklist.name << "_" << param << ",";
    comp_result_file << "\n";

    for(auto& total_score_vec: total_scores)
        total_score_vec.resize(parameters.size(), 0);

    {
        std::vector<std::jthread> threads;
        for(unsigned seed = 0; seed < SEED_COUNT; ++seed)
            threads.push_back(std::jthread([&, seed]() {
                score_once(seed, populations, total_scores, comp_result_file, score_mutex);
            }));
    }

    std::ofstream out("results/" + output_file_name + ".txt");
    boost::archive::text_oarchive oarchive(out);

    for(const auto& total_score_vec: total_scores)
        oarchive << parameters.at(std::ranges::max_element(total_score_vec) - total_score_vec.begin());
}

void run_experiment_neat()
{
    using enum ActivationFuncType;

    const std::vector<ActivationFunc> activations{ID, SIGMOID, TANH, EXP};
    const std::vector<std::vector<double>> similarities{
        {1., 1., 3., 4.},
        {1., 1., 0.4, 3.},
    };
    const std::vector<double> weight_mutation_probs{0.2, 0.4, 0.6, 0.8};
    const std::vector<double> add_node_mutation_probs{0.01, 0.02, 0.05, 0.2};
    const std::vector<double> add_connection_probs{0.02, 0.05, 0.1, 0.4};
    const std::vector<double> weight_perturbation_probs{0.3, 0.5, 0.7, 0.9};
    const std::vector<double> mutation_strengths{0.1, 0.2, 0.4, 0.6};
    const std::vector<double> crossover_probs{0.25, 0.5, 0.75, 0.9};
    const std::vector<double> inherit_connection_disabled_probs{0.25, 0.5, 0.75, 0.9};

    std::array<NEATConfig, DECK_COUNT> configs{
        NEATConfig::default_config(), NEATConfig::default_config(), NEATConfig::default_config()
    };

    run_experiment<NEAT, Network, NEATConfig, ActivationFunc>(
        configs, activations,
        [](NEATConfig& changed_config, const ActivationFunc& activation) { changed_config.activation = activation; },
        "activations"
    );

    run_experiment<NEAT, Network, NEATConfig, std::vector<double>>(
        configs, similarities,
        [](NEATConfig& changed_config, const std::vector<double>& similarity) {
            auto excess = similarity.at(0);
            auto disjoint = similarity.at(1);
            auto weight = similarity.at(2);
            auto threshold = similarity.at(3);

            changed_config.excess_coeff = excess;
            changed_config.disjoint_coeff = disjoint;
            changed_config.weight_coeff = weight;
            changed_config.similarity_threshold = threshold;
        },
        "similarities",
        std::make_pair(
            "activations",
            [](NEATConfig& config, boost::archive::text_iarchive& iarchive) { iarchive >> config.activation; }
        )
    );

    run_experiment<NEAT, Network, NEATConfig, double>(
        configs, weight_mutation_probs,
        [](NEATConfig& changed_config, const double& weight) { changed_config.weight_mutation_prob = weight; },
        "weight_mutations",
        std::make_pair(
            "similarities",
            [](NEATConfig& config, boost::archive::text_iarchive& iarchive) {
                std::vector<double> similarity;
                iarchive >> similarity;
                config.excess_coeff = similarity.at(0);
                config.disjoint_coeff = similarity.at(1);
                config.weight_coeff = similarity.at(2);
                config.similarity_threshold = similarity.at(3);
            }
        )
    );

    run_experiment<NEAT, Network, NEATConfig, double>(
        configs, add_node_mutation_probs,
        [](NEATConfig& changed_config, const double& node) { changed_config.add_node_mutation_prob = node; },
        "add_node_mutations",
        std::make_pair(
            "weight_mutations",
            [](NEATConfig& config, boost::archive::text_iarchive& iarchive) { iarchive >> config.weight_mutation_prob; }
        )
    );

    run_experiment<NEAT, Network, NEATConfig, double>(
        configs, add_connection_probs,
        [](NEATConfig& changed_config, const double& conn) { changed_config.add_connection_prob = conn; },
        "add_connections",
        std::make_pair(
            "add_node_mutations", [](NEATConfig& config, boost::archive::text_iarchive& iarchive
                                  ) { iarchive >> config.add_node_mutation_prob; }
        )
    );

    run_experiment<NEAT, Network, NEATConfig, double>(
        configs, weight_perturbation_probs,
        [](NEATConfig& changed_config, const double& weight) { changed_config.weight_perturbation_prob = weight; },
        "weight_perturbations",
        std::make_pair(
            "add_connections",
            [](NEATConfig& config, boost::archive::text_iarchive& iarchive) { iarchive >> config.add_connection_prob; }
        )
    );

    run_experiment<NEAT, Network, NEATConfig, double>(
        configs, mutation_strengths,
        [](NEATConfig& changed_config, const double& strength) { changed_config.mutation_strength = strength; },
        "mutation_strengths",
        std::make_pair(
            "weight_perturbations", [](NEATConfig& config, boost::archive::text_iarchive& iarchive
                                    ) { iarchive >> config.weight_perturbation_prob; }
        )
    );

    run_experiment<NEAT, Network, NEATConfig, double>(
        configs, crossover_probs,
        [](NEATConfig& changed_config, const double& crossover) { changed_config.crossover_prob = crossover; },
        "crossovers",
        std::make_pair(
            "mutation_strengths",
            [](NEATConfig& config, boost::archive::text_iarchive& iarchive) { iarchive >> config.mutation_strength; }
        )
    );

    run_experiment<NEAT, Network, NEATConfig, double>(
        configs, inherit_connection_disabled_probs,
        [](NEATConfig& changed_config, const double& inherit) {
            changed_config.inherit_connection_disabled_prob = inherit;
        },
        "inherit_disableds",
        std::make_pair(
            "crossovers",
            [](NEATConfig& config, boost::archive::text_iarchive& iarchive) { iarchive >> config.crossover_prob; }
        )
    );
}

void run_experiment_simple_evo()
{
    std::vector<unsigned> mu_s{20, 50, 100, 200, 500};
    std::vector<unsigned> lambdas{100, 200, 500, 1000, 2000};
    std::vector<double> init_mutation_strengths{0.05, 0.1, 0.2, 0.5, 0.7};

    std::array<EvoConfig, DECK_COUNT> configs{
        EvoConfig::default_config(), EvoConfig::default_config(), EvoConfig::default_config()
    };

    run_experiment<SimpleEvo, EvoScorer, EvoConfig, unsigned>(
        configs, mu_s, [](EvoConfig& changed_config, const unsigned& mu) { changed_config.mu = mu; }, "mus"
    );

    run_experiment<SimpleEvo, EvoScorer, EvoConfig, unsigned>(
        configs, lambdas, [](EvoConfig& changed_config, const unsigned& lambda) { changed_config.lambda = lambda; },
        "lambdas",
        std::make_pair("mus", [](EvoConfig& config, boost::archive::text_iarchive& iarchive) { iarchive >> config.mu; })
    );

    run_experiment<SimpleEvo, EvoScorer, EvoConfig, double>(
        configs, init_mutation_strengths,
        [](EvoConfig& changed_config, const double& strength) { changed_config.init_mutation_strength = strength; },
        "init_mutation_strengths",
        std::make_pair(
            "lambdas", [](EvoConfig& config, boost::archive::text_iarchive& iarchive) { iarchive >> config.lambda; }
        )
    );
}

template <unsigned Count>
void score_comparison(
    unsigned seed, unsigned iterations, const std::vector<Network>& population,
    const std::array<Decklist, Count>& decklists, std::ofstream& comp_result_file, std::mutex& score_mutex
)
{
    Rng rng(seed);

    for(unsigned iteration = 0; iteration < iterations; ++iteration)
    {
        std::array<std::vector<unsigned>, Count> scores;
        for(auto& score: scores)
            score.resize(2, 0);

        std::array<std::vector<std::unique_ptr<PlayerLogic>>, Count> deck_players;
        for(auto [players, decklist, member]: std::views::zip(deck_players, decklists, population))
        {
            players.push_back(std::make_unique<EvoPlayerLogic<Network>>(decklist, member, rng));
            players.push_back(std::make_unique<RandomPlayerLogic>(decklist, rng));
        }

        auto deck_ids = std::views::iota(0u, Count);
        auto player_ids = std::views::iota(0u, 2u);

        for(auto [fst_deck_id, fst_player_id, snd_deck_id, snd_player_id]:
            std::views::cartesian_product(deck_ids, player_ids, deck_ids, player_ids))
        {
            if(fst_player_id == snd_player_id && fst_deck_id == snd_deck_id)
                continue;

            const auto& fst_player = deck_players.at(fst_deck_id).at(fst_player_id);
            const auto& snd_player = deck_players.at(snd_deck_id).at(snd_player_id);

            auto winner = run_game(fst_player, snd_player, rng);

            switch(winner)
            {
            case GameResult::PLAYER_1:
                scores.at(fst_deck_id).at(fst_player_id)++;
                break;
            case GameResult::PLAYER_2:
                scores.at(snd_deck_id).at(snd_player_id)++;
                break;
            default:
                break;
            }
        }

        std::lock_guard lock(score_mutex);

        for(const auto& current_score_vec: scores)
            for(const auto& current: current_score_vec)
                comp_result_file << current << ",";
        comp_result_file << "\n";
    }
}

void run_comparison_neat()
{
    std::vector<Network> best_networks;

    std::ifstream warlock_in("./results/specimen/Handlock_20_ID_3_1_1_0.4_0.6_0.02_0.02_0.9_0.4_0.5_0.75_.txt");
    best_networks.emplace_back(warlock_in);

    std::ifstream hunter_in("./results/specimen/Face Hunter_20_ID_3_1_1_0.4_0.6_0.02_0.02_0.3_0.2_0.75_0.75_.txt");
    best_networks.emplace_back(hunter_in);

    std::ifstream warrior_in("./results/specimen/Control Warrior_20_ID_4_1_1_3_0.8_0.01_0.05_0.3_0.6_0.75_0.75_.txt");
    best_networks.emplace_back(warrior_in);

    std::mutex score_mutex;
    std::ofstream comp_result_file("results/vs_random.csv");

    for(const auto& decklist: decklists)
        for(const auto& type: {"NEAT", "random"})
            comp_result_file << decklist.name << "_" << type << ",";
    comp_result_file << "\n";

    {
        std::vector<std::jthread> threads;
        for(unsigned seed = 0; seed < 30; ++seed)
            threads.push_back(std::jthread([&, seed]() {
                score_comparison<DECK_COUNT>(seed, 100000, best_networks, decklists, comp_result_file, score_mutex);
            }));
    }
}

int main()
{
    run_experiment_neat();
    run_comparison_neat();
}
