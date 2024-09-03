#ifndef POWER_OVERWHELMING_H
#define POWER_OVERWHELMING_H

#include "logic/cards/SingleArgTargetFriendlyCard.h"

struct PowerOverwhelming: public SingleArgTargetFriendlyCard
{
    PowerOverwhelming(): SingleArgTargetFriendlyCard("Power Overwhelming", 1) {}

    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) override;
};

#endif