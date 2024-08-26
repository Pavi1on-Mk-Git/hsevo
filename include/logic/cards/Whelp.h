#ifndef WHELP_H
#define WHELP_H

#include "logic/cards/MinionCard.h"

struct Whelp: public MinionCard
{
    Whelp(): MinionCard("Whelp", 1, 1, 1) {}

    CLONE
};


#endif