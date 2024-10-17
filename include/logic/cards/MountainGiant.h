#ifndef MOUNTAIN_GIANT_H
#define MOUNTAIN_GIANT_H

#include "logic/cards/MinionCard.h"

class MountainGiant: public MinionCard
{
private:
    MountainGiant(): MinionCard("Mountain Giant", 12, 8, 8) {}
public:
    static const MountainGiant instance;
    unsigned mana_cost(const Game& game) const override;
};

inline const MountainGiant MountainGiant::instance;

#endif