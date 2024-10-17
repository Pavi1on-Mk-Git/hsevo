#include "logic/heroes/Hero.h"

Hero::Hero(
    const char* name, const char* hero_power_name, unsigned hero_power_mana_cost, unsigned base_health,
    const Tribe& tribe
):
    Entity(name, base_health, tribe), fatigue_dmg_(0), hero_power_name(hero_power_name),
    hero_power_mana_cost(hero_power_mana_cost), hero_power_active(true), active(true)
{}

std::vector<std::unique_ptr<HeroPowerAction>> Hero::create_hero_power_use_actions(const Game&)
{
    std::vector<std::unique_ptr<HeroPowerAction>> actions;
    actions.push_back(std::make_unique<HeroPowerAction>());
    return actions;
}

void Hero::fatigue(unsigned count)
{
    health -= count * (2 * fatigue_dmg_ + count + 1) / 2; // sum of an arithmetic sequence
    fatigue_dmg_ += count;
}
