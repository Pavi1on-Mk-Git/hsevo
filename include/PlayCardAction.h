#ifndef PLAY_CARD_ACTION_H
#define PLAY_CARD_ACTION_H

#include "Action.h"

struct PlayCardAction: Action
{
    const unsigned int hand_position, board_position;

    PlayCardAction(unsigned int hand_position, unsigned int board_position):
        hand_position(hand_position), board_position(board_position)
    {}

    void apply(Game& game);
};

#endif