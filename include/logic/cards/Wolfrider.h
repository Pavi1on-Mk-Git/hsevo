#ifndef WOLFRIDER_H
#define WOLFRIDER_H

#include "logic/cards/MinionCard.h"

class Wolfrider: public MinionCard
{
private:
    Wolfrider(): MinionCard("Wolfrider", 1, 3, 1, CHARGE) {}
public:
    static const Wolfrider instance;
};

inline const Wolfrider Wolfrider::instance;

#endif