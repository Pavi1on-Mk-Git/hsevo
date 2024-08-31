#ifndef HIT_HERO_ACTION_H
#define HIT_HERO_ACTION_H

#include "logic/Action.h"

struct HitHeroAction: Action
{
    const unsigned position;

    HitHeroAction(unsigned position);
    std::vector<Game> apply(Game& game) const;
};

#endif