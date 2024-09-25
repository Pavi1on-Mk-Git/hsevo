#ifndef INFERNAL_H
#define INFERNAL_H

#include "logic/cards/MinionCard.h"

struct Infernal: public MinionCard
{
    Infernal(): MinionCard("Infernal", 6, 6, 6, Tribe::DEMON) {}

    CLONE_CARD
};

#endif