#ifndef POWER_OVERWHELMING_H
#define POWER_OVERWHELMING_H

#include "logic/cards/Card.h"

struct PowerOverwhelming: public Card
{
    PowerOverwhelming(): Card("Power Overwhelming", 1) {}

    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) override;
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position) override;
};

#endif