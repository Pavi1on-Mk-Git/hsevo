#include "logic/Entity.h"

#include "logic/Game.h"

Entity::Entity(const char* name, unsigned base_health, const Tribe& tribe):
    name(name), max_health(base_health), health(base_health), tribe(tribe)
{}

void apply_to_entity(Game& game, const std::vector<OnPlayArg>& args, std::function<void(Entity&)> func)
{
    using enum TargetType;

    const auto target_type = std::get<TargetType>(args.at(0));

    switch(target_type)
    {
    case ALLY_HERO:
        func(*game.current_player().hero);
        break;
    case ENEMY_HERO:
        func(*game.opponent().hero);
        break;
    default:
        const auto target_position = std::get<unsigned>(args.at(1));
        if(target_type == ALLY_MINION)
            func(game.current_player().board.get_minion(target_position));
        else if(target_type == ENEMY_MINION)
            func(game.opponent().board.get_minion(target_position));
        break;
    }
}