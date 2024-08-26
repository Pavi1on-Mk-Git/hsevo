#include "logic/Minion.h"

Minion::Minion(const MinionCard& card):
    name(card.name), max_health(card.base_health), attack(card.base_attack), health(card.base_health),
    active(card.keywords & CHARGE), keywords(card.keywords)
{}

void Minion::restore_health(unsigned amount)
{
    health = std::min(max_health, health + amount);
}
