#ifndef TRADE_ACTION_H
#define TRADE_ACTION_H

#include "Action.h"

struct TradeAction: Action
{
    unsigned int first_target, second_target;
    TradeAction(unsigned int first_target, unsigned int second_target);
    void apply(Game& game);
};

#endif