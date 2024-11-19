#include "logic/Weapon.h"

Weapon::Weapon(const WeaponCard* card): card_(card), attack(card->attack), durability(card->durability) {}

const char* Weapon::name() const
{
    return card_->name;
}

void Weapon::on_secret_trigger()
{
    card_->on_secret_trigger(*this);
}