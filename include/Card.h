#ifndef CARD_H
#define CARD_H

#include <string>

struct Card
{
    const std::string name;
    const unsigned int base_mana_cost, base_attack, base_health;
    unsigned int mana_cost, attack;
    int health;
    Card(const std::string& name, unsigned int base_cost, unsigned int base_attack, unsigned int base_health);
};

#endif
