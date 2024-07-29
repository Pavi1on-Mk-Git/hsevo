#ifndef PLAY_CARD_ACTION_H
#define PLAY_CARD_ACTION_H

#include "logic/Action.h"

struct PlayCardAction: Action
{
    const unsigned hand_position, board_position, card_cost;

    PlayCardAction(unsigned hand_position, unsigned board_position, unsigned card_cost);
    void apply(Game& game);
};

#endif