#include "logic/Minion.h"

Minion::Minion(const MinionCard& card):
    Entity(card.name, card.base_health, card.tribe), attack(card.base_attack), active(card.keywords & CHARGE),
    will_die_horribly(false), keywords(card.keywords)
{}
