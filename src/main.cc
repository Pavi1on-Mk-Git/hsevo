#include <array>
#include <iostream>
#include <random>

#include "Board.h"
#include "SimpleEvo.hpp"
#include "decklists.h"

int main()
{
    auto SEED = 42u;
    auto random_engine = std::ranlux24_base(SEED);

    auto best_evo = SimpleEvo<1 + 2 * Board::MAX_BOARD_SIZE + 3>::evolve(
        10, 10, 0.0001, [&](const auto& population) { return score_member(population, ogre_deck, random_engine); }, 20,
        random_engine
    );

    std::cout << best_evo.second << std::endl;
}
