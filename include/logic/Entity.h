#ifndef ENTITY_H
#define ENTITY_H

#include <functional>
#include <string>

#include "logic/OnPlayArg.h"
#include "logic/Tribe.h"

struct Game;

class Entity
{
protected:
    Entity(std::string_view name, unsigned base_health, const Tribe& tribe = Tribe::NONE);
public:
    std::string name;
    unsigned max_health;
    int health;
    Tribe tribe;

    void restore_health(unsigned amount);
};

std::vector<Game> apply_to_entity(Game& game, const std::vector<OnPlayArg>& args, std::function<void(Entity&)> func);

#endif