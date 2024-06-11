#include "PlayerState.h"

static const auto default_max_health = 30;

PlayerState::PlayerState(DeckList decklist, std::ranlux24_base& random_engine):
    _max_health(default_max_health), _fatigue_dmg(0), health(default_max_health), mana_crystals(0), mana(0),
    deck(decklist, random_engine)
{}

void PlayerState::fatigue(unsigned int count)
{
    health -= count * (2 * _fatigue_dmg + count + 1) / 2; // sum of an arithmetic sequence
    _fatigue_dmg += count;
}
