#include <fstream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include "ai/NEAT.h"
#include "ai/SimpleEvo.hpp"
#include "ai/evo_functions.hpp"
#include "logic/decklists.h"
#include "logic/run_game.h"
#include "players/EvoPlayerLogic.hpp"
#include "utils/Rng.h"

int main()
{
    spdlog::set_default_logger(spdlog::basic_logger_mt("file_logger", "logs/hsevo.log", true));
    spdlog::set_pattern("[%l] %v");
    spdlog::set_level(spdlog::level::off);

    const int SEED = 42;
    Rng::instance().seed(SEED);

    NEATConfig config{
        .population_size = 20,
        .iterations = 20,
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

    const std::vector<Decklist> decklists = get_decklists();

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

        warlock_population.epoch();
        hunter_population.epoch();
        warrior_population.epoch();
    }
}
