#ifndef TRADE_ACTION_H
#define TRADE_ACTION_H

#include "logic/Action.h"

struct TradeAction: Action
{
    unsigned first_target, second_target;
    TradeAction(unsigned first_target, unsigned second_target);
    void apply(Game& game);
};

#endif