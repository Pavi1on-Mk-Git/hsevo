#ifndef PLAYER_H
#define PLAYER_H

#include "logic/PlayerState.h"
#include "players/PlayerLogic.h"

struct Player
{
    const std::unique_ptr<PlayerLogic>& logic;
    PlayerState state;
    Player(const std::unique_ptr<PlayerLogic>& logic);
};

#endif