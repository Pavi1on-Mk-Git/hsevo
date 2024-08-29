#ifndef MINION_H
#define MINION_H

#include "logic/Entity.h"
#include "logic/MinionKeywords.h"
#include "logic/cards/MinionCard.h"

struct Minion: public Entity
{
    unsigned attack;
    bool active;
    MinionKeywords keywords;
    Minion(const MinionCard& card);
};


#endif