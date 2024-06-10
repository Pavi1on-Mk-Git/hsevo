#include "Card.h"

Card::Card(const std::string& name, unsigned int base_cost, unsigned int base_attack, unsigned int base_health):
    name(name), base_cost(base_cost), base_attack(base_attack), base_health(base_health), cost(base_cost),
    attack(base_attack), health(base_health)
{}
