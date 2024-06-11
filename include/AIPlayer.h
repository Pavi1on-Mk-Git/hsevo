#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "Action.h"
#include "Board.h"
#include "Deck.h"
#include "Hand.h"

class AIPlayer
{
private:
    unsigned int _max_health;
    unsigned int _fatigue_dmg;
    std::ranlux24_base& _random_engine;
public:
    int health;
    unsigned int mana_crystals, mana;
    Deck deck;
    Hand hand;
    Board board;

    AIPlayer(DeckList decklist, std::ranlux24_base& random_engine);
    void fatigue(unsigned int count);
    std::unique_ptr<Action> choose_action(std::vector<std::unique_ptr<Action>> actions);
};

#endif