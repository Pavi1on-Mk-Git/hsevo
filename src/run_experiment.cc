#include <boost/archive/text_oarchive.hpp>
#include <format>
#include <fstream>

#include "ai/NEAT.h"
#include "ai/evo_functions.hpp"
#include "logic/decklists.h"
#include "utils/Rng.h"

static const unsigned SEED_COUNT = 20;

static const std::vector<Decklist> decklists = get_decklists();

void experiment(const NEATConfig& config)
{
    std::vector<unsigned> warlock_scores, hunter_scores, warrior_scores;
    warlock_scores.resize(config.iterations, 0);
    hunter_scores.resize(config.iterations, 0);
    warrior_scores.resize(config.iterations, 0);

    std::vector<Network> best_warlocks, best_hunters, best_warriors;
    best_warlocks.reserve(SEED_COUNT);
    best_hunters.reserve(SEED_COUNT);
    best_warriors.reserve(SEED_COUNT);

    for(unsigned seed = 0; seed < SEED_COUNT; ++seed)
    {
        Rng::instance().seed(seed);

        NEAT warlock_population(config), hunter_population(config), warrior_population(config);
        std::optional<std::pair<Network, unsigned>> best_warlock, best_hunter, best_warrior;

        for(unsigned iteration = 0; iteration < config.iterations; ++iteration)
        {
            auto scores = score_populations(
                std::vector<std::vector<Network>>{
                    warlock_population.networks(), hunter_population.networks(), warrior_population.networks()
                },
                decklists
            );

            best_warlock = warlock_population.assign_scores(scores.at(0));
            best_hunter = hunter_population.assign_scores(scores.at(1));
            best_warrior = warrior_population.assign_scores(scores.at(2));

            warlock_scores.at(iteration) += best_warlock->second;
            hunter_scores.at(iteration) += best_hunter->second;
            warrior_scores.at(iteration) += best_warrior->second;

            warlock_population.epoch();
            hunter_population.epoch();
            warrior_population.epoch();
        }

        best_warlocks.push_back(best_warlock->first);
        best_hunters.push_back(best_hunter->first);
        best_warriors.push_back(best_warrior->first);
    }

    auto average_over_seeds = [](unsigned sum) { return sum / SEED_COUNT; };

    std::ranges::transform(warlock_scores, warlock_scores.begin(), average_over_seeds);
    std::ranges::transform(hunter_scores, hunter_scores.begin(), average_over_seeds);
    std::ranges::transform(warrior_scores, warrior_scores.begin(), average_over_seeds);

    auto final_scores = score_populations(
        std::vector<std::vector<Network>>{best_warlocks, best_hunters, best_warriors}, decklists
    );

    auto best_warlock = best_warlocks.at(std::ranges::max_element(final_scores.at(0)) - final_scores.at(0).begin());
    auto best_hunter = best_hunters.at(std::ranges::max_element(final_scores.at(1)) - final_scores.at(1).begin());
    auto best_warrior = best_warriors.at(std::ranges::max_element(final_scores.at(2)) - final_scores.at(2).begin());

    auto file_suffix = config.name();

    std::ofstream warlock_out(std::format("results/networks/warlock_{}.txt", file_suffix));
    std::ofstream hunter_out(std::format("results/networks/hunter_{}.txt", file_suffix));
    std::ofstream warrior_out(std::format("results/networks/warrior_{}.txt", file_suffix));

    best_warlock.save(warlock_out);
    best_hunter.save(hunter_out);
    best_warrior.save(warrior_out);

    std::ofstream results(std::format("results/scores/{}", file_suffix));
    boost::archive::text_oarchive archive(results);

    archive << warlock_scores << hunter_scores << warrior_scores;
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
