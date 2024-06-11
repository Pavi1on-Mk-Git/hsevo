#ifndef PLAY_CARD_ACTION_H
#define PLAY_CARD_ACTION_H

#include "Action.h"

struct PlayCardAction: Action
{
    const unsigned int hand_position, board_position, card_cost;

    PlayCardAction(unsigned int hand_position, unsigned int board_position, unsigned int card_cost);
    void apply(Game& game);
};

#endif