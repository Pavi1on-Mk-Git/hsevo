#ifndef EAGLEHORN_BOW_H
#define EAGLEHORN_BOW_H

#include "logic/cards/WeaponCard.h"

class EaglehornBow: public WeaponCard
{
private:
    EaglehornBow(): WeaponCard("Eaglehorn Bow", 3, 3, 2) {}
public:
    static const EaglehornBow instance;
    void on_secret_trigger(Weapon& weapon) const override;
};

inline const EaglehornBow EaglehornBow::instance;

#endif