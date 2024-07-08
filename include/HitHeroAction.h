#ifndef HIT_HERO_ACTION_H
#define HIT_HERO_ACTION_H

#include "Action.h"

struct HitHeroAction: Action
{
    unsigned position;
    HitHeroAction(unsigned position);
    void apply(Game& game);
};

#endif