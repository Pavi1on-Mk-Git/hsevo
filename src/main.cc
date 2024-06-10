#include <array>
#include <random>

#include "Game.h"
#include "decklists.h"

int main()
{
    auto SEED = 42u;
    auto random_engine = std::ranlux24_base(SEED);

    std::array<AIPlayer, 2> players = {AIPlayer(ogre_deck, random_engine), AIPlayer(ogre_deck, random_engine)};

    auto game = Game(std::move(players), random_engine);
    game.run();
}
