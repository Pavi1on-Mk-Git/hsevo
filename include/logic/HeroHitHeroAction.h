#ifndef HERO_HIT_HERO_ACTION_H
#define HERO_HIT_HERO_ACTION_H

#include "logic/Action.h"

struct HeroHitHeroAction: Action
{
    HeroHitHeroAction();
    std::vector<Game> apply(Game& game) const;
    std::deque<GuiElementId> element_sequence() const override;
};

#endif