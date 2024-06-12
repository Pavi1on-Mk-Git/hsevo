#ifndef RANDOM_PLAYER_LOGIC_H
#define RANDOM_PLAYER_LOGIC_H

#include <random>

#include "Action.h"
#include "PlayerLogic.h"

struct RandomPlayerLogic: PlayerLogic
{
    std::ranlux24_base& random_engine;
    RandomPlayerLogic(const DeckList& decklist, std::ranlux24_base& random_engine);
    std::unique_ptr<Action> choose_action(const Game& game, std::vector<std::unique_ptr<Action>> actions)
        const override;
};

#endif