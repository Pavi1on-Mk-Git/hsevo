#ifndef PLAYER_H
#define PLAYER_H

#include "logic/Hero.h"
#include "players/PlayerLogic.h"

struct Player
{
    std::shared_ptr<PlayerLogic> logic;
    Hero hero;
    Player(std::shared_ptr<PlayerLogic> logic);
};

#endif