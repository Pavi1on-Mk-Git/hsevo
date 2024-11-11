#ifndef REXXAR_H
#define REXXAR_H

#include "logic/heroes/Hero.h"

struct Rexxar: public Hero
{
    Rexxar(): Hero("Rexxar", "Steady Shot", 2, 30) {}

    CLONE_HERO

    void on_hero_power_use(Game& game, const std::vector<OnPlayArg>& args) override;
};

#endif