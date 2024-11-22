#ifndef KORKRON_ELITE_H
#define KORKRON_ELITE_H

#include "logic/cards/MinionCard.h"

class KorkronElite: public MinionCard
{
private:
    KorkronElite(): MinionCard("Kor'kron Elite", 4, 4, 3, CHARGE) {}
public:
    static const KorkronElite instance;
};

inline const KorkronElite KorkronElite::instance;

#endif