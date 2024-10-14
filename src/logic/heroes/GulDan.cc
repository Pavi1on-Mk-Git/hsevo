#include "logic/heroes/GulDan.h"

#include "logic/Game.h"

std::vector<Game> GulDan::on_hero_power_use(Game& game, const std::vector<OnPlayArg>&)
{
    game.current_player().hero->health -= 2;
    game.draw();
    return {game};
}
