#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "Deck.h"
#include "Hand.h"

class AIPlayer
{
public:
    Deck deck;
    Hand hand;

    AIPlayer(DeckList decklist, std::ranlux24_base& random_engine);
};

#endif