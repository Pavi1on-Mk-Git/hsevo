#include "logic/heroes/Hero.h"

Hero::Hero(
    const char* name, const char* hero_power_name, unsigned hero_power_mana_cost, unsigned base_health,
    const Tribe& tribe
):
    Entity(name, base_health, tribe), fatigue_dmg_(0), hero_power_name(hero_power_name),
    hero_power_mana_cost(hero_power_mana_cost), hero_power_active(true), active(true), armour(0)
{}

void Hero::restore_health(unsigned amount)
{
    health = std::min(max_health, health + amount);
}

void Hero::deal_dmg(unsigned amount, Game&)
{
    if(amount > armour)
    {
        health -= amount - armour;
        armour = 0;
    }
    else
        armour -= amount;
}

void Hero::fatigue(unsigned count)
{
    health -= count * (2 * fatigue_dmg_ + count + 1) / 2; // sum of an arithmetic sequence
    fatigue_dmg_ += count;
}
