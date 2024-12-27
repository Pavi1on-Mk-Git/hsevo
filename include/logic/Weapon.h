#ifndef WEAPON_H
#define WEAPON_H

#include "logic/cards/WeaponCard.h"

/**
 * Represents a weapon equipped by a hero
 */
class Weapon
{
private:
    /**
     * Underlying weapon card
     */
    const WeaponCard* card_;
public:
    /**
     * Attack and durability of the weapon
     */
    unsigned attack, durability;

    /**
     * Construct a weapon from card
     * @param card Underlying card
     */
    Weapon(const WeaponCard* card);

    /**
     * Return name of the weapon
     * @return Name of the weapon
     */
    const char* name() const;

    /**
     * Calls `on_secret_trigger` of the underlying card
     */
    void on_secret_trigger();
};

#endif