#ifndef MOUNTAIN_GIANT_H
#define MOUNTAIN_GIANT_H

#include "logic/cards/MinionCard.h"

struct MountainGiant: public MinionCard
{
    MountainGiant(): MinionCard("Mountain Giant", 12, 8, 8) {}

    CLONE_CARD

    unsigned mana_cost(const Game& game) const override;
};

#endif