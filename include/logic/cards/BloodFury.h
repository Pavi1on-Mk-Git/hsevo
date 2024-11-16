#ifndef BLOOD_FURY_H
#define BLOOD_FURY_H

#include "logic/cards/WeaponCard.h"

class BloodFury: public WeaponCard
{
private:
    BloodFury(): WeaponCard("Blood Fury", 3, 3, 8) {}
public:
    static const BloodFury instance;
};

inline const BloodFury BloodFury::instance;

#endif