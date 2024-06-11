#include "AIPlayer.h"

static const auto default_max_health = 30;

AIPlayer::AIPlayer(DeckList decklist, std::ranlux24_base& random_engine):
    max_health(default_max_health), fatigue_dmg(0), health(default_max_health), deck(decklist, random_engine), hand()
{}

void AIPlayer::fatigue(unsigned int count)
{
    health -= count * (2 * fatigue_dmg + count + 1) / 2; // sum of arithmetic sequence
    fatigue_dmg += count;
}
