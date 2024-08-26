#ifndef MOLTEN_GIANT_H
#define MOLTEN_GIANT_H

#include "logic/cards/MinionCard.h"

struct MoltenGiant: public MinionCard
{
    MoltenGiant(): MinionCard("Molten Giant", 20, 8, 8) {}

    CLONE

    unsigned mana_cost(const Game& game) const override;
};

#endif