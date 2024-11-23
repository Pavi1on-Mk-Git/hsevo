#ifndef ENTITY_H
#define ENTITY_H

#include <functional>

#include "logic/OnPlayArg.h"
#include "logic/Tribe.h"

struct Game;

class Entity
{
protected:
    Entity(const char* name, unsigned base_health, const Tribe& tribe);
public:
    const char* name;
    unsigned max_health;
    int health;
    Tribe tribe;

    virtual void restore_health(unsigned amount) = 0;
    virtual void deal_dmg(unsigned amount, Game& game) = 0;
};

void apply_to_entity(Game& game, const std::vector<OnPlayArg>& args, std::function<void(Entity&)> func);

#endif