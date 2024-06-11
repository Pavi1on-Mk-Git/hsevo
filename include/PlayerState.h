#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "Action.h"
#include "Board.h"
#include "Deck.h"
#include "Hand.h"

class PlayerState
{
private:
    unsigned int _max_health;
    unsigned int _fatigue_dmg;
public:
    int health;
    unsigned int mana_crystals, mana;
    Deck deck;
    Hand hand;
    Board board;

    PlayerState(DeckList decklist, std::ranlux24_base& random_engine);
    void fatigue(unsigned int count);
};

#endif