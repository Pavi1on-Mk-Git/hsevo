#ifndef BOULDERFIST_OGRE_H
#define BOULDERFIST_OGRE_H

#include "logic/cards/MinionCard.h"

class BoulderfistOgre: public MinionCard
{
private:
    BoulderfistOgre(): MinionCard("Boulderfist Ogre", 6, 6, 7) {}
public:
    static const BoulderfistOgre instance;
};

inline const BoulderfistOgre BoulderfistOgre::instance;

#endif