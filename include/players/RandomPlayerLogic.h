#ifndef RANDOM_PLAYER_LOGIC_H
#define RANDOM_PLAYER_LOGIC_H


#include "logic/Action.h"
#include "players/PlayerLogic.h"

struct RandomPlayerLogic: PlayerLogic
{
    RandomPlayerLogic(const Decklist& decklist);
    Game choose_and_apply_action(Game& game, std::vector<std::unique_ptr<Action>> actions) const override;
};

#endif