#ifndef MINION_H
#define MINION_H

#include "Card.h"

struct Minion
{
    std::string name;
    unsigned int base_attack, base_health;
    unsigned int attack;
    int health;
    bool active;
    Minion(const Card& card);
};


#endif