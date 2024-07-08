#include "PlayerState.h"

static const unsigned int DEFAULT_MAX_HEALTH = 30;

PlayerState::PlayerState(DeckList decklist, std::ranlux24_base& random_engine):
    max_health_(DEFAULT_MAX_HEALTH), fatigue_dmg_(0), health(DEFAULT_MAX_HEALTH), mana_crystals(0), mana(0),
    deck(decklist, random_engine)
{}

void PlayerState::fatigue(unsigned int count)
{
    health -= count * (2 * fatigue_dmg_ + count + 1) / 2; // sum of an arithmetic sequence
    fatigue_dmg_ += count;
}
