#ifndef WEAPON_CARD_H
#define WEAPON_CARD_H

#include "logic/cards/Card.h"

struct Weapon;

/**
 * Base class for all cards representing weapons
 */
class WeaponCard: public Card
{
protected:
    /**
     * Construct a weapon card with provided arguments
     * @param name Name of the card
     * @param mana_cost Cost of the card
     * @param attack Base attack of the card
     * @param durability Base durability of the card
     */
    WeaponCard(const char* name, unsigned mana_cost, unsigned attack, unsigned durability);
public:
    /**
     * Base attack and durability of the weapon
     */
    const unsigned attack, durability;

    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;

    /**
     * Modify a weapon when a secret is triggered
     * @param weapon Weapon to modify
     */
    virtual void on_secret_trigger(Weapon& weapon) const;
};

#endif