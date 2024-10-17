#ifndef MOLTEN_GIANT_H
#define MOLTEN_GIANT_H

#include "logic/cards/MinionCard.h"

class MoltenGiant: public MinionCard
{
private:
    MoltenGiant(): MinionCard("Molten Giant", 20, 8, 8) {}
public:
    static const MoltenGiant instance;
    unsigned mana_cost(const Game& game) const override;
};

inline const MoltenGiant MoltenGiant::instance;

#endif