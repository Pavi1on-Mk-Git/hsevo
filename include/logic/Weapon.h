#ifndef WEAPON_H
#define WEAPON_H

#include <string>

struct Weapon
{
    std::string name;
    unsigned attack, durability;

    Weapon(std::string_view name, unsigned attack, unsigned durability);
};

#endif