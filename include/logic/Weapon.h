#ifndef WEAPON_H
#define WEAPON_H

struct Weapon
{
    const char* name;
    unsigned attack, durability;

    Weapon(const char* name, unsigned attack, unsigned durability);
};

#endif