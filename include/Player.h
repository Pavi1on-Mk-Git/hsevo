#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerLogic.h"
#include "PlayerState.h"

struct Player
{
    const std::unique_ptr<PlayerLogic>& logic;
    PlayerState state;
    Player(const std::unique_ptr<PlayerLogic>& logic, std::ranlux24_base& random_engine);
};

#endif