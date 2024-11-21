#ifndef FIERY_WAR_AXE_H
#define FIERY_WAR_AXE_H

#include "logic/cards/WeaponCard.h"

class FieryWarAxe: public WeaponCard
{
private:
    FieryWarAxe(): WeaponCard("Fiery War Axe", 2, 3, 2) {}
public:
    static const FieryWarAxe instance;
};

inline const FieryWarAxe FieryWarAxe::instance;

#endif