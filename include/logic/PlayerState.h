#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "logic/Action.h"
#include "logic/Board.h"
#include "logic/Deck.h"
#include "logic/Hand.h"
#include "logic/Tribe.h"

class PlayerState
{
private:
    unsigned max_health_;
    unsigned fatigue_dmg_;
public:
    int health;
    unsigned mana_crystals, mana;
    Tribe tribe;
    Deck deck;
    Hand hand;
    Board board;

    PlayerState(const Decklist& decklist, const Tribe& tribe = Tribe::NONE);
    void fatigue(unsigned count);
    void restore_health(unsigned amount);
};

#endif