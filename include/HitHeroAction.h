#ifndef HIT_HERO_ACTION_H
#define HIT_HERO_ACTION_H

#include "Action.h"

struct HitHeroAction: Action
{
    unsigned int position;
    HitHeroAction(unsigned int position);
    void apply(Game& game);
};

#endif