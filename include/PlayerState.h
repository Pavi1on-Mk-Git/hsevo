#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "Action.h"
#include "Board.h"
#include "Deck.h"
#include "Hand.h"

class PlayerState
{
private:
    unsigned max_health_;
    unsigned fatigue_dmg_;
public:
    int health;
    unsigned mana_crystals, mana;
    Deck deck;
    Hand hand;
    Board board;

    PlayerState(DeckList decklist);
    void fatigue(unsigned count);
};

#endif