#ifndef MINION_H
#define MINION_H

#include "logic/Card.h"
#include "logic/MinionKeywords.h"

struct Minion
{
    std::string name;
    unsigned base_attack, base_health;
    unsigned attack;
    int health;
    bool active;
    MinionKeywords keywords;
    Minion(const Card& card);
};


#endif