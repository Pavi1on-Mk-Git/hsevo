#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/array.hpp>
#include <format>
#include <fstream>
#include <thread>

#include "ai/NEAT.h"
#include "ai/evo_functions.hpp"
#include "logic/decklists.h"
#include "utils/Rng.h"

static const unsigned SEED_COUNT = 30;
static const unsigned ITERATIONS = 30;
static const std::array<Decklist, DECK_COUNT> decklists = get_decklists();

void single_seed_experiment(unsigned seed, const std::array<NEATConfig, DECK_COUNT>& configs)
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
}

const unsigned COMPARISON_SEED = 42;

void experiment(const std::array<NEATConfig, DECK_COUNT>& configs)
{
    std::array<std::string, DECK_COUNT> file_suffixes;
    std::ranges::transform(configs, file_suffixes.begin(), [](const NEATConfig& config) { return config.name(); });

    {
        std::vector<std::jthread> threads;

        for(unsigned seed = 19; seed < 20; ++seed)
            threads.push_back(std::jthread([&, seed]() { single_seed_experiment(seed, configs); }));
    }
}

int main()
{
    using enum ActivationFuncType;
    const std::vector<std::vector<double>> similarities{
        {1., 1., 0.4, 3.},
    };

    std::array<NEATConfig, DECK_COUNT> configs{default_config(), default_config(), default_config()};

    // Similarities
    {
        configs.at(0).activation = ActivationFuncType::SIGMOID;
        configs.at(1).activation = ActivationFuncType::ID;
        configs.at(2).activation = ActivationFuncType::SIGMOID;

        std::array<std::vector<Network>, DECK_COUNT> populations;

        for(const auto& similarity: similarities)
        {
            auto changed_configs = configs;
            for(auto& changed_config: changed_configs)
            {
                auto excess = similarity.at(0);
                auto disjoint = similarity.at(1);
                auto weight = similarity.at(2);
                auto threshold = similarity.at(3);

                changed_config.excess_coeff = excess;
                changed_config.disjoint_coeff = disjoint;
                changed_config.weight_coeff = weight;
                changed_config.similarity_threshold = threshold;
            }

            experiment(changed_configs);
        }
    }
}
