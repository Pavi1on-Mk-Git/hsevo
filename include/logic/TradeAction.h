#ifndef TRADE_ACTION_H
#define TRADE_ACTION_H

#include "logic/Action.h"

struct TradeAction: Action
{
    const unsigned first_target, second_target;
    TradeAction(unsigned first_target, unsigned second_target);
    std::vector<Game> apply(Game& game) const;
    std::deque<GuiElementId> element_sequence() const override;
};

#endif