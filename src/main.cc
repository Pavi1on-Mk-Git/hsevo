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

    auto best_evo = NEAT::evolve({
        .population_size = 10,
        .iterations = 20,
        .scoring_func = [&](const auto& population) { return score_member(population, control_warrior()); },
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
    });

    std::ofstream out("results/test.txt");
    best_evo.first.save(out);

    // std::ifstream in("results/test.txt");
    // Network best_evo(in);

    spdlog::set_level(spdlog::level::debug);

    // SPDLOG_DEBUG("Best player achieved score: {}", best_evo.second);

    auto deck = control_warrior();
    // std::unique_ptr<PlayerLogic> logic = std::make_unique<EvoPlayerLogic<Network>>(deck, best_evo);
    std::unique_ptr<PlayerLogic> logic = std::make_unique<EvoPlayerLogic<Network>>(deck, best_evo.first);
    run_game(logic, logic);
}
