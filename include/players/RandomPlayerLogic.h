#ifndef RANDOM_PLAYER_LOGIC_H
#define RANDOM_PLAYER_LOGIC_H

#include <random>

#include "logic/Action.h"
#include "players/PlayerLogic.h"

struct RandomPlayerLogic: PlayerLogic
{
    RandomPlayerLogic(const DeckList& decklist);
    std::unique_ptr<Action> choose_action(const Game& game, std::vector<std::unique_ptr<Action>> actions)
        const override;
};

#endif