#ifndef BOULDERFIST_OGRE_H
#define BOULDERFIST_OGRE_H

#include "logic/cards/MinionCard.h"

struct BoulderfistOgre: public MinionCard
{
    BoulderfistOgre(): MinionCard("Boulderfist Ogre", 6, 6, 7) {}

    CLONE_CARD
};

#endif