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
        .inherit_connection_disabled_prob = 0.75,
    };

    const auto decklists = get_decklists();

    std::array<NEAT, DECK_COUNT> populations{config, config, config};
    std::array<std::optional<std::pair<Network, unsigned>>, DECK_COUNT> current_bests;

    for(unsigned iteration = 0; iteration < config.iterations; ++iteration)
    {
        std::array<std::vector<Network>, DECK_COUNT> iteration_networks;
        std::ranges::transform(populations, iteration_networks.begin(), [](const NEAT& neat) {
            return neat.networks();
        });

        auto iteration_scores = score_populations<Network, DECK_COUNT>(iteration_networks, decklists);

        for(auto [best, population, new_scores]: std::views::zip(current_bests, populations, iteration_scores))
        {
            best = population.assign_scores(new_scores);
            population.epoch();
        }
    }
}
