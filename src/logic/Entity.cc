#include "logic/Entity.h"

#include "logic/Game.h"

Entity::Entity(std::string_view name, unsigned base_health, const Tribe& tribe):
    name(name), max_health(base_health), health(base_health), tribe(tribe)
{}

void Entity::restore_health(unsigned amount)
{
    health = std::min(max_health, health + amount);
}

std::vector<Game> apply_to_entity(Game& game, const std::vector<OnPlayArg>& args, std::function<void(Entity&)> func)
{
    const auto target_type = std::get<TargetType>(args.at(0));

    switch(target_type)
    {
    case TargetType::ALLY_HERO:
        func(game.current_player().hero);
        break;
    case TargetType::ENEMY_HERO:
        func(game.opponent().hero);
        break;
    default:
        const auto target_position = std::get<unsigned>(args.at(1));
        if(target_type == TargetType::ALLY_MINION)
            func(game.current_player().hero.board.get_minion(target_position));
        else if(target_type == TargetType::ENEMY_MINION)
            func(game.opponent().hero.board.get_minion(target_position));
        break;
    }

    return {game};
}