#ifndef END_TURN_ACTION_H
#define END_TURN_ACTION_H

#include "logic/Action.h"

struct EndTurnAction: Action
{
    std::vector<Game> apply(const Game& game) const override;
    std::vector<Game> test_apply(const Game& game) const override;
    std::deque<GuiElementId> element_sequence() const override;
};

#endif