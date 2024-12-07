#include <format>
#include <fstream>
#include <thread>

#include "ai/NEAT.h"
#include "ai/evo_functions.hpp"
#include "logic/decklists.h"
#include "utils/Rng.h"

static const unsigned SEED_COUNT = 3;
static const std::array<Decklist, DECK_COUNT> decklists = get_decklists();

void single_seed_experiment(
    unsigned seed, const NEATConfig& config, std::mutex& data_mutex,
    std::array<std::ofstream, DECK_COUNT>& result_files, std::array<std::vector<Network>, DECK_COUNT>& best_networks
)
{
    Rng::instance().seed(seed);

    std::array<NEAT, DECK_COUNT> populations{config, config, config};
    std::array<std::vector<Network>, DECK_COUNT> hall_of_champions;
    std::array<unsigned, DECK_COUNT> champion_scores;
    std::array<std::vector<unsigned>, DECK_COUNT> score_history;
    for(auto& score_vec: score_history)
        score_vec.reserve(config.iterations);

    for(unsigned iteration = 0; iteration < config.iterations; ++iteration)
    {
        std::array<std::vector<Network>, DECK_COUNT> iteration_networks;
        std::ranges::transform(populations, iteration_networks.begin(), [](const NEAT& neat) {
            return neat.networks();
        });
        std::array<std::optional<std::pair<Network, unsigned>>, DECK_COUNT> iteration_bests;

        auto iteration_scores = score_populations<Network, DECK_COUNT>(iteration_networks, decklists);

        for(auto [best, population, new_scores, champions, decklist, champion_score, score_vec]: std::views::zip(
                iteration_bests, populations, iteration_scores, hall_of_champions, decklists, champion_scores,
                score_history
            ))
        {
            best = population.assign_scores(new_scores);

            auto contender_score = score_hall_of_champions(champions, best->first, decklist);

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

void experiment(const NEATConfig& config)
{
    const auto file_suffix = config.name();

    std::mutex data_mutex;

    std::array<std::ofstream, DECK_COUNT> result_files;
    std::ranges::transform(decklists, result_files.begin(), [&](const Decklist& deck) {
        return std::ofstream(std::format("results/scores/{}_{}", deck.name, file_suffix));
    });

    std::array<std::vector<Network>, DECK_COUNT> best_networks;
    for(auto& network_vec: best_networks)
        network_vec.reserve(SEED_COUNT);

    {
        std::vector<std::jthread> threads;

        for(unsigned seed = 0; seed < SEED_COUNT; ++seed)
            threads.push_back(std::jthread([&]() {
                single_seed_experiment(seed, config, data_mutex, result_files, best_networks);
            }));
    }

    auto final_scores = score_populations<Network, DECK_COUNT>(best_networks, decklists);

    for(auto [bests, deck_final_scores, decklist]: std::views::zip(best_networks, final_scores, decklists))
    {
        auto the_best = bests.at(std::ranges::max_element(deck_final_scores) - deck_final_scores.begin());

        std::ofstream out(std::format("results/networks/{}_{}.txt", decklist.name, file_suffix));
        the_best.save(out);
    }
}

int main()
{
    using enum ActivationFuncType;

    const auto config = default_config();

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

    experiment(config);
}
