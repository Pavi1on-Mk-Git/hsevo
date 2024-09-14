#include "logic/heroes/GulDan.h"

#include "logic/Game.h"

std::vector<Game> GulDan::on_hero_power_use(Game& game, const std::vector<OnPlayArg>& args)
{
    static_cast<void>(args);

    game.current_player().hero->health -= 2;
    game.draw();
    return {game};
}

std::vector<std::unique_ptr<HeroPowerAction>> GulDan::create_hero_power_use_actions(const Game& game)
{
    static_cast<void>(game);

    std::vector<std::unique_ptr<HeroPowerAction>> actions;
    actions.push_back(std::make_unique<HeroPowerAction>());
    return actions;
}