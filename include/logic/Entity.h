#ifndef ENTITY_H
#define ENTITY_H

#include <functional>

#include "logic/OnPlayArg.h"
#include "logic/Tribe.h"

struct Game;

/**
 * Base class for all entities with health and tribe present in the game
 */
class Entity
{
protected:
    /**
     * Construct an entity
     * @param name Name of the entity
     * @param base_health Base health of the entity
     * @param tribe Tribe of the entity
     */
    Entity(const char* name, unsigned base_health, const Tribe& tribe);
public:
    /**
     * Name of the entity
     */
    const char* name;

    /**
     * Maximum health of the entity
     */
    unsigned max_health;

    /**
     * Current health of the entity
     */
    int health;

    /**
     * Tribe of the entity
     */
    Tribe tribe;

    /**
     * Restore provided amount of health to the entity
     * @param amount Amount of health to restore
     */
    virtual void restore_health(unsigned amount) = 0;

    /**
     * Deal provided amount of damage to the entity
     * @param amount Amount of damage to deal
     * @param game Game state
     */
    virtual void deal_dmg(unsigned amount, Game& game) = 0;
};

/**
 * Use the provided function on an entity specified in the `args` parameter from the provided game state
 * @param game Game state
 * @param args Arguments specifying which entity to choose
 * @param func Function to apply to the selected entity
 */
void apply_to_entity(Game& game, const std::vector<OnPlayArg>& args, std::function<void(Entity&)> func);

#endif