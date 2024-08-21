#ifndef MOUNTAIN_GIANT_H
#define MOUNTAIN_GIANT_H

#include "logic/cards/Card.h"

struct MountainGiant: public Card
{
    MountainGiant(): Card("Mountain Giant", 12, 8, 8) {}

    CLONE

    unsigned mana_cost(const Game& game) const override;
};

#endif