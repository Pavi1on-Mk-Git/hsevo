#include "logic/Card.h"

Card::Card(const std::string& name, unsigned base_cost, unsigned base_attack, unsigned base_health):
    name(name), base_mana_cost(base_cost), base_attack(base_attack), base_health(base_health), mana_cost(base_cost),
    attack(base_attack), health(base_health)
{}
