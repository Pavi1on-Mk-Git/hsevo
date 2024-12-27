#include "logic/heroes/GulDan.h"

#include "logic/Game.h"

std::unique_ptr<Hero> GulDan::clone() const
{
    return std::make_unique<GulDan>(*this);
}

const unsigned LIFE_TAP_DMG = 2;

void GulDan::on_hero_power_use(Game& game)
{
    game.current_player().hero->deal_dmg(LIFE_TAP_DMG, game);
    game.draw();
}
