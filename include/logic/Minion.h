#ifndef MINION_H
#define MINION_H

#include "logic/MinionKeywords.h"
#include "logic/cards/MinionCard.h"

struct Minion
{
    std::string name;
    unsigned max_health;
    unsigned attack;
    int health;
    bool active;
    MinionKeywords keywords;
    Tribe tribe;
    Minion(const MinionCard& card);
    void restore_health(unsigned amount);
};


#endif