#include "AIPlayer.h"

static const auto default_max_health = 30;

AIPlayer::AIPlayer(DeckList decklist, std::ranlux24_base& random_engine):
    _max_health(default_max_health), _fatigue_dmg(0), _random_engine(random_engine), health(default_max_health),
    mana_crystals(0), mana(0), deck(decklist, random_engine)
{}

void AIPlayer::fatigue(unsigned int count)
{
    health -= count * (2 * _fatigue_dmg + count + 1) / 2; // sum of an arithmetic sequence
    _fatigue_dmg += count;
}

std::unique_ptr<Action> AIPlayer::choose_action(std::vector<std::unique_ptr<Action>> actions)
{
    return std::move(actions.at(_random_engine() % actions.size()));
}
