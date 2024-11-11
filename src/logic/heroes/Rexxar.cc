#include "logic/heroes/Rexxar.h"

#include "logic/Game.h"

const unsigned STEADY_SHOT_DMG = 2;

void Rexxar::on_hero_power_use(Game& game, const std::vector<OnPlayArg>&)
{
    game.opponent().hero->health -= STEADY_SHOT_DMG;
}
