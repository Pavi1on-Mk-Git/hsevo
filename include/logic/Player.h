#ifndef PLAYER_H
#define PLAYER_H

#include "logic/Hero.h"
#include "players/PlayerLogic.h"

struct Player
{
    const std::unique_ptr<PlayerLogic>& logic;
    Hero hero;
    Player(const std::unique_ptr<PlayerLogic>& logic);
};

#endif