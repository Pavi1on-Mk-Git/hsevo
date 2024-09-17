#include <array>
#include <iostream>
#include <random>

#include "ai/SimpleEvo.hpp"
#include "logic/Board.h"
#include "logic/decklists.h"

int main()
{
    int SEED = 42;
    Rng::instance()->seed(SEED);

    auto best_evo = SimpleEvo<1 + 2 * Board::MAX_BOARD_SIZE + 3>::evolve(
        10, 10, 0.0001, [&](const auto& population) { return score_member(population, handlock()); }, 20
    );

    std::cout << best_evo.second << std::endl;
}
