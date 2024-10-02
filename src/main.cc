#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include "ai/SimpleEvo.hpp"
#include "logic/Board.h"
#include "logic/decklists.h"
#include "logic/run_game.h"
#include "players/EvoPlayerLogic.h"

int main()
{
    spdlog::set_default_logger(spdlog::basic_logger_mt("file_logger", "logs/hsevo.log", true));
    spdlog::set_pattern("[%l] %v");
    spdlog::set_level(spdlog::level::off);

    int SEED = 42;
    Rng::instance()->seed(SEED);

    auto best_evo = SimpleEvo<GameStateInput::INPUT_SIZE>::evolve(
        10, 10, 0.0001, [&](const auto& population) { return score_member(population, handlock()); }, 20
    );

    spdlog::set_level(spdlog::level::debug);

    SPDLOG_DEBUG("Best player achieved score: {}", best_evo.second);

    auto deck = handlock();
    std::unique_ptr<PlayerLogic> logic = std::make_unique<EvoPlayerLogic>(deck, best_evo.first);
    run_game(logic, logic);
}
