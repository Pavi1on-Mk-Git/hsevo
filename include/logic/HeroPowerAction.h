#ifndef HERO_POWER_ACTION_H
#define HERO_POWER_ACTION_H

#include "logic/Action.h"
#include "logic/OnPlayArg.h"

/**
 * Action of using the hero power of the player's hero
 */
struct HeroPowerAction: Action
{
    std::vector<Game> apply(const Game& game) const override;
    std::vector<Game> test_apply(const Game& game) const override;
    std::deque<GuiElementId> element_sequence() const override;
};

#endif