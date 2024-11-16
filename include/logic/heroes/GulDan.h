// I realize it should be written as Gul'dan but character set disallows it
#ifndef GUL_DAN_H
#define GUL_DAN_H

#include "logic/heroes/Hero.h"

using Villain = Hero; // this is deep

struct GulDan: public Villain
{
    GulDan(): Villain("Gul'Dan", "Life Tap", 2, 30) {}

    std::unique_ptr<Hero> clone() const override;
    void on_hero_power_use(Game& game, const std::vector<OnPlayArg>& args) override;
};

#endif