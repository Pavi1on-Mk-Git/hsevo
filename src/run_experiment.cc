#include <boost/archive/text_oarchive.hpp>
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
    std::array<std::ofstream, DECK_COUNT>& result_files, std::array<std::vector<Network>, DECK_COUNT>& best_networks
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
    for(auto [score_vec, config]: std::views::zip(score_history, configs))
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

    std::mutex data_mutex;

    std::array<std::ofstream, DECK_COUNT> result_files;
    for(auto [file, decklist, suffix]: std::views::zip(result_files, decklists, file_suffixes))
        file = std::ofstream(std::format("results/scores/{}_{}", decklist.name, suffix));

    std::array<std::vector<Network>, DECK_COUNT> best_networks;
    for(auto& network_vec: best_networks)
        network_vec.reserve(SEED_COUNT);

    {
        std::vector<std::jthread> threads;

        for(unsigned seed = 0; seed < SEED_COUNT; ++seed)
            threads.push_back(std::jthread([&]() {
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

int main()
{
    using enum ActivationFuncType;

    const std::vector<ActivationFunc> activations{ID, SIGMOID, TANH, EXP};
    const std::vector<std::tuple<double, double, double, double>> similarities{
        {4., 1., 1., 3.},
        {3., 1., 1., 0.4},
    };
    const std::vector<double> weight_mutation_probs{0.2, 0.4, 0.6, 0.8};
    const std::vector<double> add_node_mutation_probs{0.01, 0.02, 0.05, 0.2};
    const std::vector<double> add_connection_probs{0.02, 0.05, 0.1, 0.4};
    const std::vector<double> weight_perturbation_probs{0.3, 0.5, 0.7, 0.9};
    const std::vector<double> mutation_strengths{0.1, 0.2, 0.4, 0.6};
    const std::vector<double> crossover_probs{0.25, 0.5, 0.75, 0.9};
    const std::vector<double> inherit_connection_disabled_probs{0.25, 0.5, 0.75, 0.9};

    std::array<NEATConfig, DECK_COUNT> configs{default_config(), default_config(), default_config()};
    std::array<std::vector<Network>, DECK_COUNT> populations;

    for(const auto& activation: activations)
    {
        auto changed_configs = configs;
        for(auto& changed_config: changed_configs)
            changed_config.activation = activation;

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
        total_score_vec.resize(activations.size(), 0);

    auto score_once = [&](unsigned seed) {
        Rng rng(seed);

        for(auto [total_score_vec, current_score_vec]:
            std::views::zip(total_scores, score_populations<Network, DECK_COUNT>(populations, decklists, rng)))
        {
            std::lock_guard lock(score_mutex);

            for(auto [total, current]: std::views::zip(total_score_vec, current_score_vec))
                total += current;
        }
    };

    {
        std::vector<std::jthread> threads;
        for(unsigned seed = 0; seed < SEED_COUNT; ++seed)
            threads.push_back(std::jthread([&]() { score_once(seed); }));
    }

    std::ofstream out("results/hyper.txt");
    boost::archive::text_oarchive archive(out);

    for(const auto& total_score_vec: total_scores)
        archive << activations.at(std::ranges::max_element(total_score_vec) - total_score_vec.begin());
}
