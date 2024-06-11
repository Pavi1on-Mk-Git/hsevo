#include <array>
#include <iostream>
#include <random>

#include "Game.h"
#include "decklists.h"

int main()
{
    auto SEED = 42u;
    auto random_engine = std::ranlux24_base(SEED);

    std::vector<RandomPlayerLogic> players = {
        RandomPlayerLogic(ogre_deck, random_engine), RandomPlayerLogic(ogre_deck, random_engine)};

    auto game = Game(players.at(0), players.at(1), random_engine);
    auto winner = game.run();
    std::cout << "The winner is " << winner.value_or(-1) << std::endl;
}
