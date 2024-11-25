#ifndef PLAY_MINION_ACTION_H
#define PLAY_MINION_ACTION_H


#include "logic/PlayCardAction.h"

struct PlayMinionAction: public PlayCardAction
{
    const unsigned board_position;

    PlayMinionAction(
        unsigned hand_position, unsigned card_cost, unsigned board_position, const std::vector<OnPlayArg>& args = {}
    );
    std::vector<Game> apply(const Game& game) const override;
    std::vector<Game> test_apply(const Game& game) const override;
    std::deque<GuiElementId> element_sequence() const override;
};

#endif