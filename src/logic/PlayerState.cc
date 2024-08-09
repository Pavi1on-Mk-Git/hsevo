#include "logic/PlayerState.h"

static const unsigned DEFAULT_MAX_HEALTH = 30;

PlayerState::PlayerState(DeckList decklist):
    max_health_(DEFAULT_MAX_HEALTH), fatigue_dmg_(0), health(DEFAULT_MAX_HEALTH), mana_crystals(0), mana(0),
    deck(decklist)
{}

void PlayerState::fatigue(unsigned count)
{
    health -= count * (2 * fatigue_dmg_ + count + 1) / 2; // sum of an arithmetic sequence
    fatigue_dmg_ += count;
}

void PlayerState::restore_health(unsigned amount)
{
    health = std::min(max_health_, health + amount);
}
