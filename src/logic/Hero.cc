#include "logic/Hero.h"

static const unsigned DEFAULT_MAX_HEALTH = 30;

Hero::Hero(const Decklist& decklist, const Tribe& tribe):
    Entity("", DEFAULT_MAX_HEALTH, tribe), fatigue_dmg_(0), mana_crystals(0), mana(0), deck(decklist)
{}

void Hero::fatigue(unsigned count)
{
    health -= count * (2 * fatigue_dmg_ + count + 1) / 2; // sum of an arithmetic sequence
    fatigue_dmg_ += count;
}
