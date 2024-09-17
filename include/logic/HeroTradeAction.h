#ifndef HERO_TRADE_ACTION_H
#define HERO_TRADE_ACTION_H

#include "logic/Action.h"

struct HeroTradeAction: Action
{
    const unsigned position;

    HeroTradeAction(unsigned position);
    std::vector<Game> apply(Game& game) const;
};

#endif