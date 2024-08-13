#include "logic/Minion.h"

Minion::Minion(const Card& card):
    name(card.name), max_health(card.base_health), attack(card.attack), health(card.health),
    active(card.keywords & CHARGE), keywords(card.keywords)
{}

void Minion::restore_health(unsigned amount)
{
    health = std::min(max_health, health + amount);
}
