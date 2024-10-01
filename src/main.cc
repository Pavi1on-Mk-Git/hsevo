#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include "ai/SimpleEvo.hpp"
#include "logic/Board.h"
#include "logic/decklists.h"
#include "logic/run_game.h"
#include "players/EvoPlayerLogic.h"

int main()
{
    spdlog::set_default_logger(spdlog::basic_logger_mt("file_logger", "logs/hsevo.log"));
    spdlog::set_pattern("[%@] [%l] %v");
    spdlog::set_level(spdlog::level::off);

    int SEED = 42;
    Rng::instance()->seed(SEED);

    auto best_evo = SimpleEvo<1 + 2 * Board::MAX_BOARD_SIZE + 3>::evolve(
        10, 10, 0.0001, [&](const auto& population) { return score_member(population, handlock()); }, 20
    );

    SPDLOG_DEBUG("Best player achieved score: {}", best_evo.second);

    auto deck = handlock();
    auto logic = std::make_shared<EvoPlayerLogic>(deck, best_evo.first);
    run_game(logic, logic);
}
