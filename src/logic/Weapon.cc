#include "logic/Weapon.h"

Weapon::Weapon(std::string_view name, unsigned attack, unsigned durability):
    name(name), attack(attack), durability(durability)
{}