#ifndef SHADOWFLAME_H
#define SHADOWFLAME_H

#include "logic/cards/SingleArgTargetFriendlyMinionCard.h"

struct Shadowflame: public SingleArgTargetFriendlyMinionCard
{
    Shadowflame(): SingleArgTargetFriendlyMinionCard("Shadowflame", 4) {}

    CLONE_CARD

    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) override;
};

#endif