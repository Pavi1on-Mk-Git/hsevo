#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "Action.h"
#include "Board.h"
#include "Deck.h"
#include "Hand.h"

class AIPlayer
{
private:
    unsigned int max_health;
    unsigned int fatigue_dmg;
public:
    int health;
    Deck deck;
    Hand hand;
    Board board;

    AIPlayer(DeckList decklist, std::ranlux24_base& random_engine);
    void fatigue(unsigned int count);
    std::unique_ptr<Action> choose_action(std::vector<std::unique_ptr<Action>> actions);
};

#endif