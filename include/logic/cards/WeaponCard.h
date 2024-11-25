#ifndef WEAPON_CARD_H
#define WEAPON_CARD_H

#include "logic/cards/Card.h"

struct Weapon;

class WeaponCard: public Card
{
protected:
    WeaponCard(const char* name, unsigned mana_cost, unsigned attack, unsigned durability);
public:
    const unsigned attack, durability;

    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;
    virtual void on_secret_trigger(Weapon& weapon) const;
};

#endif