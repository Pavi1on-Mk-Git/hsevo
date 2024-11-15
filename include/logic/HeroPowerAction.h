#ifndef HERO_POWER_ACTION_H
#define HERO_POWER_ACTION_H

#include "logic/Action.h"
#include "logic/OnPlayArg.h"

struct HeroPowerAction: Action
{
    const std::vector<OnPlayArg> args;

    HeroPowerAction(const std::vector<OnPlayArg>& args = {});
    std::vector<Game> apply(Game& game) const override;
    std::deque<GuiElementId> element_sequence() const override;
};

#endif