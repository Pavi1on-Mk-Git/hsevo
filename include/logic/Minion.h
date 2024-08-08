#ifndef MINION_H
#define MINION_H

#include "logic/Card.h"
#include "logic/MinionKeywords.h"

struct Minion
{
    std::string name;
    unsigned max_health;
    unsigned attack;
    int health;
    bool active;
    MinionKeywords keywords;
    Minion(const Card& card);
    void restore_health(unsigned amount);
};


#endif