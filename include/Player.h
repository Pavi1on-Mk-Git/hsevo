#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerState.h"
#include "RandomPlayerLogic.h"

struct Player
{
    const RandomPlayerLogic& logic;
    PlayerState state;
    Player(const RandomPlayerLogic& logic);
};

#endif