#ifndef HOUND_H
#define HOUND_H

#include "logic/cards/MinionCard.h"

class Hound: public MinionCard
{
private:
    Hound(): MinionCard("Hound", 1, 1, 1, CHARGE, Tribe::BEAST) {}
public:
    static const Hound instance;
};

inline const Hound Hound::instance;

#endif