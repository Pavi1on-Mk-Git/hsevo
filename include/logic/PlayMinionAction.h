#ifndef PLAY_MINION_ACTION_H
#define PLAY_MINION_ACTION_H


#include "logic/PlayCardAction.h"

struct PlayMinionAction: public PlayCardAction
{
    const unsigned board_position;

    PlayMinionAction(
        unsigned hand_position, unsigned card_cost, unsigned board_position, const std::vector<OnPlayArg>& args = {}
    );
    void apply(Game& game);
};

#endif