#ifndef WHELP_H
#define WHELP_H

#include "logic/cards/MinionCard.h"

class Whelp: public MinionCard
{
private:
    Whelp(): MinionCard("Whelp", 1, 1, 1, Tribe::DRAGON) {}
public:
    static const Whelp instance;
};

inline const Whelp Whelp::instance;


#endif