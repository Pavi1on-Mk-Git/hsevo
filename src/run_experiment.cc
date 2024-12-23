#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/array.hpp>
#include <filesystem>
#include <format>
#include <fstream>
#include <thread>

#include "ai/NEAT.h"
#include "ai/evo_functions.hpp"
#include "logic/decklists.h"
#include "utils/Rng.h"

static const unsigned SEED_COUNT = 30;
static const unsigned ITERATIONS = 1000;
static const std::array<Decklist, DECK_COUNT> decklists = get_decklists();

void single_seed_experiment(
    unsigned seed, const std::array<NEATConfig, DECK_COUNT>& configs, std::mutex& data_mutex,
    std::vector<std::ofstream>& result_files, std::array<std::vector<Network>, DECK_COUNT>& best_networks
)
{
    Rng rng(seed);

    std::vector<NEAT> populations;
    std::ranges::transform(configs, std::back_inserter(populations), [&](const NEATConfig& config) {
        return NEAT(config, rng);
    });

    std::array<std::vector<Network>, DECK_COUNT> hall_of_champions;
    std::array<unsigned, DECK_COUNT> champion_scores;
    std::array<std::vector<unsigned>, DECK_COUNT> score_history;
    for(auto& score_vec: score_history)
        score_vec.reserve(ITERATIONS);

    for(unsigned iteration = 0; iteration < ITERATIONS; ++iteration)
    {
        std::array<std::vector<Network>, DECK_COUNT> iteration_networks;
        std::ranges::transform(populations, iteration_networks.begin(), [](const NEAT& neat) {
            return neat.networks();
        });
        std::array<std::optional<std::pair<Network, unsigned>>, DECK_COUNT> iteration_bests;

        auto iteration_scores = score_populations<Network, DECK_COUNT>(iteration_networks, decklists, rng);

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

    for(auto [network_vec, champions]: std::views::zip(best_networks, hall_of_champions))
        network_vec.push_back(champions.back());

    for(auto [result_file, scores]: std::views::zip(result_files, score_history))
    {
        std::ranges::copy(scores, std::ostream_iterator<unsigned>(result_file, ","));
        result_file << '\n';
    }
}

const unsigned COMPARISON_SEED = 42;

void experiment(const std::array<NEATConfig, DECK_COUNT>& configs)
{
    std::array<std::string, DECK_COUNT> file_suffixes;
    std::ranges::transform(configs, file_suffixes.begin(), [](const NEATConfig& config) { return config.name(); });

    for(auto [decklist, suffix]: std::views::zip(decklists, file_suffixes))
        if(std::filesystem::exists(
               std::filesystem::path(std::format("results/networks/{}_{}.txt", decklist.name, suffix))
           ))
            return;

    std::mutex data_mutex;

    std::vector<std::ofstream> result_files;
    for(auto [decklist, suffix]: std::views::zip(decklists, file_suffixes))
        result_files.push_back(std::ofstream(std::format("results/scores/{}_{}", decklist.name, suffix)));

    std::array<std::vector<Network>, DECK_COUNT> best_networks;
    for(auto& network_vec: best_networks)
        network_vec.reserve(SEED_COUNT);

    {
        std::vector<std::jthread> threads;

        for(unsigned seed = 0; seed < SEED_COUNT; ++seed)
            threads.push_back(std::jthread([&, seed]() {
                single_seed_experiment(seed, configs, data_mutex, result_files, best_networks);
            }));
    }

    Rng rng(COMPARISON_SEED);

    auto final_scores = score_populations<Network, DECK_COUNT>(best_networks, decklists, rng);

    for(auto [bests, deck_final_scores, decklist, suffix]:
        std::views::zip(best_networks, final_scores, decklists, file_suffixes))
    {
        auto the_best = bests.at(std::ranges::max_element(deck_final_scores) - deck_final_scores.begin());

        std::ofstream out(std::format("results/networks/{}_{}.txt", decklist.name, suffix));
        the_best.save(out);
    }
}

void score_once(
    unsigned seed, const std::array<std::vector<Network>, DECK_COUNT>& populations,
    std::array<std::vector<unsigned>, DECK_COUNT>& total_scores, std::mutex& score_mutex
)
{
    Rng rng(seed);

    for(auto [total_score_vec, current_score_vec]:
        std::views::zip(total_scores, score_populations<Network, DECK_COUNT>(populations, decklists, rng)))
    {
        std::lock_guard lock(score_mutex);

        for(auto [total, current]: std::views::zip(total_score_vec, current_score_vec))
            total += current;
    }
};

template <typename Param>
void run_experiment(
    std::array<NEATConfig, DECK_COUNT>& configs, const std::vector<Param>& parameters,
    const std::function<void(NEATConfig&, const Param&)>& param_setter, const std::string& output_file_name,
    const std::optional<std::pair<std::string, std::function<void(NEATConfig&, boost::archive::text_iarchive&)>>>&
        input_data = std::nullopt
)
{
    if(input_data)
    {
        auto [name, config_loader] = *input_data;

        std::ifstream in(name);
        boost::archive::text_iarchive iarchive(in);

        for(auto& config: std::views::reverse(configs))
            config_loader(config, iarchive);
    }

    std::array<std::vector<Network>, DECK_COUNT> populations;

    for(const auto& param: parameters)
    {
        auto changed_configs = configs;
        for(auto& changed_config: changed_configs)
            param_setter(changed_config, param);

        experiment(changed_configs);

        std::vector<Network> results;
        for(auto [decklist, config]: std::views::zip(decklists, changed_configs))
        {
            std::ifstream in(std::format("results/networks/{}_{}.txt", decklist.name, config.name()));
            results.emplace_back(in);
        }

        for(auto [result, population]: std::views::zip(results, populations))
            population.push_back(result);
    }

    std::mutex score_mutex;
    std::array<std::vector<unsigned>, DECK_COUNT> total_scores;
    for(auto& total_score_vec: total_scores)
        total_score_vec.resize(parameters.size(), 0);

    {
        std::vector<std::jthread> threads;
        for(unsigned seed = 0; seed < SEED_COUNT; ++seed)
            threads.push_back(std::jthread([&, seed]() { score_once(seed, populations, total_scores, score_mutex); }));
    }

    std::ofstream out(output_file_name);
    boost::archive::text_oarchive oarchive(out);

    for(const auto& total_score_vec: total_scores)
        oarchive << parameters.at(std::ranges::max_element(total_score_vec) - total_score_vec.begin());
}

int main()
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

    std::array<NEATConfig, DECK_COUNT> configs{default_config(), default_config(), default_config()};

    run_experiment<ActivationFunc>(
        configs, activations,
        [](NEATConfig& changed_config, const ActivationFunc& activation) { changed_config.activation = activation; },
        "results/hyper_activations.txt"
    );

    run_experiment<std::vector<double>>(
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
        "results/hyper_similarities.txt",
        std::make_pair(
            "results/hyper_activations.txt",
            [](NEATConfig& config, boost::archive::text_iarchive& iarchive) { iarchive >> config.activation; }
        )
    );

    run_experiment<double>(
        configs, weight_mutation_probs,
        [](NEATConfig& changed_config, const double& weight) { changed_config.weight_mutation_prob = weight; },
        "results/hyper_weight_mutations.txt",
        std::make_pair(
            "results/hyper_similarities.txt",
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

    run_experiment<double>(
        configs, add_node_mutation_probs,
        [](NEATConfig& changed_config, const double& node) { changed_config.add_node_mutation_prob = node; },
        "results/hyper_add_node_mutations.txt",
        std::make_pair(
            "results/hyper_weight_mutations.txt",
            [](NEATConfig& config, boost::archive::text_iarchive& iarchive) { iarchive >> config.weight_mutation_prob; }
        )
    );

    run_experiment<double>(
        configs, add_connection_probs,
        [](NEATConfig& changed_config, const double& conn) { changed_config.add_connection_prob = conn; },
        "results/hyper_add_connections.txt",
        std::make_pair(
            "results/hyper_add_node_mutations.txt", [](NEATConfig& config, boost::archive::text_iarchive& iarchive
                                                    ) { iarchive >> config.add_node_mutation_prob; }
        )
    );

    run_experiment<double>(
        configs, weight_perturbation_probs,
        [](NEATConfig& changed_config, const double& weight) { changed_config.weight_perturbation_prob = weight; },
        "results/hyper_weight_perturbations.txt",
        std::make_pair(
            "results/hyper_add_connections.txt",
            [](NEATConfig& config, boost::archive::text_iarchive& iarchive) { iarchive >> config.add_connection_prob; }
        )
    );

    run_experiment<double>(
        configs, mutation_strengths,
        [](NEATConfig& changed_config, const double& strength) { changed_config.mutation_strength = strength; },
        "results/hyper_mutation_strengths.txt",
        std::make_pair(
            "results/hyper_weight_perturbations.txt", [](NEATConfig& config, boost::archive::text_iarchive& iarchive
                                                      ) { iarchive >> config.weight_perturbation_prob; }
        )
    );

    run_experiment<double>(
        configs, crossover_probs,
        [](NEATConfig& changed_config, const double& crossover) { changed_config.crossover_prob = crossover; },
        "results/hyper_crossovers.txt",
        std::make_pair(
            "results/hyper_mutation_strengths.txt",
            [](NEATConfig& config, boost::archive::text_iarchive& iarchive) { iarchive >> config.mutation_strength; }
        )
    );

    run_experiment<double>(
        configs, inherit_connection_disabled_probs,
        [](NEATConfig& changed_config, const double& inherit) {
            changed_config.inherit_connection_disabled_prob = inherit;
        },
        "results/hyper_inherit_disableds.txt",
        std::make_pair(
            "results/hyper_crossovers.txt",
            [](NEATConfig& config, boost::archive::text_iarchive& iarchive) { iarchive >> config.crossover_prob; }
        )
    );
}
