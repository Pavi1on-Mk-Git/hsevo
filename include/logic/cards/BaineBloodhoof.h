#ifndef BAINE_BLOODHOOF_H
#define BAINE_BLOODHOOF_H

#include "logic/cards/MinionCard.h"

class BaineBloodhoof: public MinionCard
{
private:
    BaineBloodhoof(): MinionCard("Baine Bloodhoof", 6, 4, 5) {}
public:
    static const BaineBloodhoof instance;
};

inline const BaineBloodhoof BaineBloodhoof::instance;

#endif