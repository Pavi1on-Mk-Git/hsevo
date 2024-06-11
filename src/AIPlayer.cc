#include "AIPlayer.h"

static const auto default_max_health = 30;

AIPlayer::AIPlayer(DeckList decklist, std::ranlux24_base& random_engine):
    max_health(default_max_health), fatigue_dmg(0), health(default_max_health), deck(decklist, random_engine)
{}

void AIPlayer::fatigue(unsigned int count)
{
    health -= count * (2 * fatigue_dmg + count + 1) / 2; // sum of an arithmetic sequence
    fatigue_dmg += count;
}

std::unique_ptr<Action> AIPlayer::choose_action(std::vector<std::unique_ptr<Action>> actions)
{
    return std::move(actions.at(0));
}
