#ifndef LORD_JARAXXUS_H
#define LORD_JARAXXUS_H

#include "logic/heroes/Hero.h"

struct LordJaraxxus: public Hero
{
    LordJaraxxus(): Hero("Lord Jaraxxus", "INFERNO!", 2, 15, Tribe::DEMON) {}

    std::unique_ptr<Hero> clone() const override;
    void on_hero_power_use(Game& game);
};

#endif