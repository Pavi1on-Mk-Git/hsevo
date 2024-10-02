#ifndef PLAYER_H
#define PLAYER_H

#include "logic/Board.h"
#include "logic/Deck.h"
#include "logic/Hand.h"
#include "logic/heroes/Hero.h"
#include "players/PlayerLogic.h"

struct Player
{
    static constexpr unsigned MAX_MANA = 10;

    std::unique_ptr<Hero> hero;
    unsigned mana_crystals, mana;
    Deck deck;
    Hand hand;
    Board board;

    Player(const Decklist& decklist);
    Player(const Player& other);
    Player& operator=(Player&& other) = default;
};

#endif