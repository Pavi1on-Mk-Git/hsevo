#include "logic/heroes/Hero.h"

static const unsigned DEFAULT_MAX_HEALTH = 30;

Hero::Hero(std::string_view name, std::string_view hero_power_name, unsigned hero_power_mana_cost, const Tribe& tribe):
    Entity(name, DEFAULT_MAX_HEALTH, tribe), fatigue_dmg_(0), hero_power_name(hero_power_name),
    hero_power_mana_cost(hero_power_mana_cost), hero_power_active(true)
{}

void Hero::fatigue(unsigned count)
{
    health -= count * (2 * fatigue_dmg_ + count + 1) / 2; // sum of an arithmetic sequence
    fatigue_dmg_ += count;
}
