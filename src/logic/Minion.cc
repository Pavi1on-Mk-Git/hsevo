#include "logic/Minion.h"

Minion::Minion(const Card& card):
    name(card.name), base_attack(card.base_attack), base_health(card.base_health), attack(card.attack),
    health(card.health), active(false), keywords(card.keywords)
{}

void Minion::restore_health(unsigned amount)
{
    health = std::min(base_health, health + amount);
}
