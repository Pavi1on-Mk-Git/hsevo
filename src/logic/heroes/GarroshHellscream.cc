#include "logic/heroes/GarroshHellscream.h"

#include "logic/Game.h"

std::unique_ptr<Hero> GarroshHellscream::clone() const
{
    return std::make_unique<GarroshHellscream>(*this);
}

const unsigned ARMOUR_UP_ARMOR = 2;

void GarroshHellscream::on_hero_power_use(Game& game)
{
    game.current_player().hero->armour += ARMOUR_UP_ARMOR;
}