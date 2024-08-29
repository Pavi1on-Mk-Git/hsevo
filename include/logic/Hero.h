#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "logic/Board.h"
#include "logic/Deck.h"
#include "logic/Entity.h"
#include "logic/Hand.h"

class Hero: public Entity
{
private:
    unsigned fatigue_dmg_;
public:
    unsigned mana_crystals, mana;
    Deck deck;
    Hand hand;
    Board board;

    Hero(const Decklist& decklist, const Tribe& tribe = Tribe::NONE);
    void fatigue(unsigned count);
};

#endif