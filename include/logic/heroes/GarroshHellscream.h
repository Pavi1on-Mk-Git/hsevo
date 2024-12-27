#ifndef GARROSH_HELLSCREAM_H
#define GARROSH_HELLSCREAM_H

#include "logic/heroes/Hero.h"

struct GarroshHellscream: public Hero
{
    GarroshHellscream(): Hero("Garrosh Hellscream", "Armor Up!", 2, 30) {}

    std::unique_ptr<Hero> clone() const override;
    void on_hero_power_use(Game& game) override;
};

#endif