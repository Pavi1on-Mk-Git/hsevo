#include "logic/heroes/Rexxar.h"

#include "logic/Game.h"

std::unique_ptr<Hero> Rexxar::clone() const
{
    return std::make_unique<Rexxar>(*this);
}

const unsigned STEADY_SHOT_DMG = 2;

void Rexxar::on_hero_power_use(Game& game, const std::vector<OnPlayArg>&)
{
    game.opponent().hero->deal_dmg(STEADY_SHOT_DMG, game);
}
