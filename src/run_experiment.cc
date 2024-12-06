#include <boost/archive/text_oarchive.hpp>
#include <format>
#include <fstream>

#include "ai/NEAT.h"
#include "ai/evo_functions.hpp"
#include "logic/decklists.h"
#include "utils/Rng.h"

static const unsigned SEED_COUNT = 20;

static const std::array<Decklist, DECK_COUNT> decklists = get_decklists();

void experiment(const NEATConfig& config)
{
    std::array<std::vector<unsigned>, DECK_COUNT> scores;

    for(auto& score_vec: scores)
        score_vec.resize(config.iterations, 0);

    std::array<std::vector<Network>, DECK_COUNT> best_networks;

    for(auto& network_vec: best_networks)
        network_vec.reserve(SEED_COUNT);

    for(unsigned seed = 0; seed < SEED_COUNT; ++seed)
    {
        Rng::instance().seed(seed);

        std::array<NEAT, DECK_COUNT> populations{config, config, config};
        std::array<std::optional<std::pair<Network, unsigned>>, DECK_COUNT> current_bests;

        for(unsigned iteration = 0; iteration < config.iterations; ++iteration)
        {
            std::array<std::vector<Network>, DECK_COUNT> iteration_networks;
            std::ranges::transform(populations, iteration_networks.begin(), [](const NEAT& neat) {
                return neat.networks();
            });

            auto iteration_scores = score_populations<Network, DECK_COUNT>(iteration_networks, decklists);

            for(auto [best, population, new_scores, total_scores]:
                std::views::zip(current_bests, populations, iteration_scores, scores))
            {
                best = population.assign_scores(new_scores);
                total_scores.at(iteration) += best->second;
                population.epoch();
            }

            for(auto [bests, current_best]: std::views::zip(best_networks, current_bests))
                bests.push_back(current_best->first);
        }
    }

    auto average_over_seeds = [](unsigned sum) { return sum / SEED_COUNT; };

    auto file_suffix = config.name();
    std::ofstream results(std::format("results/scores/{}", file_suffix));
    boost::archive::text_oarchive archive(results);

    for(auto& score_vec: scores)
    {
        std::ranges::transform(score_vec, score_vec.begin(), average_over_seeds);
        archive << score_vec;
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
    NEATConfig config{
        .population_size = 20,
        .iterations = 5,
        .activation = ActivationFuncType::ID,
        .similarity_threshold = 4.,
        .excess_coeff = 1.,
        .disjoint_coeff = 1.,
        .weight_coeff = 3.,
        .weight_mutation_prob = 0.8,
        .add_node_mutation_prob = 0.02,
        .add_connection_prob = 0.05,
        .weight_perturbation_prob = 0.9,
        .mutation_strength = 0.2,
        .crossover_prob = 0.75,
        .interspecies_mating_prob = 0.001,
        .inherit_connection_disabled_prob = 0.75,
    };

    experiment(config);
}
