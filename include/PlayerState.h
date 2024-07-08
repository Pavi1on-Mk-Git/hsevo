#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "Action.h"
#include "Board.h"
#include "Deck.h"
#include "Hand.h"

class PlayerState
{
private:
    unsigned int max_health_;
    unsigned int fatigue_dmg_;
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