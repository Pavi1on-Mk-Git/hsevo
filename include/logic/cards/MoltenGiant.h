#ifndef MOLTEN_GIANT_H
#define MOLTEN_GIANT_H

#include "logic/cards/Card.h"

struct MoltenGiant: public Card
{
    MoltenGiant(): Card("Molten Giant", 20, 8, 8) {}

    CLONE

    unsigned mana_cost(const Game& game) const override;
};

#endif