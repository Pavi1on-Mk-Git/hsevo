#include "logic/cards/EaglehornBow.h"

#include "logic/Weapon.h"

void EaglehornBow::on_secret_trigger(Weapon& weapon) const
{
    ++weapon.durability;
}
