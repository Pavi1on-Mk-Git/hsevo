#ifndef BOULDERFIST_OGRE_H
#define BOULDERFIST_OGRE_H

#include "logic/cards/Card.h"

struct BoulderfistOgre: public Card
{
    BoulderfistOgre(): Card("Boulderfist Ogre", 6, 6, 7) {}

    CLONE
};

#endif