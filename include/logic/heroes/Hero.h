#ifndef HERO_H
#define HERO_H

#include <memory>
#include <optional>

#include "logic/Entity.h"
#include "logic/HeroPowerAction.h"
#include "logic/Weapon.h"

/**
 * Base class for all heroes present in the game
 */
class Hero: public Entity
{
private:
    /**
     * Damage which the hero will receive the next time he draws a card from an empty deck
     */
    unsigned fatigue_dmg_;
protected:
    /**
     * Construct a hero
     * @param name Name of the hero
     * @param name Name of the hero's hero power
     * @param hero_power_mana_cost Base cost of the hero's hero power
     * @param base_health Base health of the hero
     * @param tribe Tribe of the hero
     */
    Hero(
        const char* name, const char* hero_power_name, unsigned hero_power_mana_cost, unsigned base_health,
        const Tribe& tribe = Tribe::NONE
    );
public:
    /**
     * Name of the hero's hero power
     */
    const char* hero_power_name;

    /**
     * Base cost of the hero's hero power
     */
    unsigned hero_power_mana_cost;

    /**
     * Flag signaling if the hero's hero power is currently active
     */
    bool hero_power_active;

    /**
     * Flag signaling if the hero can currently attack
     */
    bool active;

    /**
     * Weapon used currently by the hero (`std::nullopt` if the hero has no weapon)
     */
    std::optional<Weapon> weapon;

    /**
     * Amount of armour present on the hero
     */
    unsigned armour;

    virtual ~Hero() = default;

    void restore_health(unsigned amount) override;
    void deal_dmg(unsigned amount, Game& game) override;

    /**
     * Modify the game state by using the hero's hero power
     * @param game Game state
     */
    virtual void on_hero_power_use(Game& game) = 0;

    /**
     * Clone the hero
     * @return Copy of the hero
     */
    virtual std::unique_ptr<Hero> clone() const = 0;

    /**
     * Deal fatigue damage to the hero based on the amount of cards drawn
     * @param count Amount of cards drawn
     */
    void fatigue(unsigned count);
};

#endif