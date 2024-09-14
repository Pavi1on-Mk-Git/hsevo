#ifndef PLAYER_H
#define PLAYER_H

#include "logic/Board.h"
#include "logic/Deck.h"
#include "logic/Hand.h"
#include "logic/heroes/Hero.h"
#include "players/PlayerLogic.h"

struct Player
{
    std::shared_ptr<PlayerLogic> logic;
    std::unique_ptr<Hero> hero;
    unsigned mana_crystals, mana;
    Deck deck;
    Hand hand;
    Board board;

    Player(std::shared_ptr<PlayerLogic> logic);
    Player(const Player& other);
    Player& operator=(Player&& other) = default;
};

#endif