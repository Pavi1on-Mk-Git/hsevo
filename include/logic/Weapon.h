#ifndef WEAPON_H
#define WEAPON_H

#include "logic/cards/WeaponCard.h"

class Weapon
{
private:
    const WeaponCard* card_;
public:
    unsigned attack, durability;

    Weapon(const WeaponCard* card);
    const char* name() const;
    void on_secret_trigger();
};

#endif