#ifndef INFERNAL_H
#define INFERNAL_H

#include "logic/cards/MinionCard.h"

class Infernal: public MinionCard
{
private:
    Infernal(): MinionCard("Infernal", 6, 6, 6, Tribe::DEMON) {}
public:
    static const Infernal instance;
};

inline const Infernal Infernal::instance;

#endif