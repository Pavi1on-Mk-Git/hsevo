#ifndef POWER_OVERWHELMING_H
#define POWER_OVERWHELMING_H

#include "logic/cards/SingleArgTargetFriendlyMinionCard.h"

struct PowerOverwhelming: public SingleArgTargetFriendlyMinionCard
{
    PowerOverwhelming(): SingleArgTargetFriendlyMinionCard("Power Overwhelming", 1) {}

    CLONE_CARD

    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) override;
};

#endif