#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include "ai/NEAT.h"
#include "ai/SimpleEvo.h"
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

    int SEED = 42;
    Rng::instance()->seed(SEED);

    auto best_evo = NEAT::evolve(
        {10, 20, [&](const auto& population) { return score_member(population, handlock()); },
         [](double value) { return value; }, 4., 1., 1., 3., 0.8, 0.02, 0.05, 0.9, 0.2, 0.75, 0.001, 0.75}
    );

    spdlog::set_level(spdlog::level::debug);

    SPDLOG_DEBUG("Best player achieved score: {}", best_evo.second);

    auto deck = handlock();
    std::unique_ptr<PlayerLogic> logic = std::make_unique<EvoPlayerLogic<Network>>(deck, best_evo.first);
    run_game(logic, logic);
}
