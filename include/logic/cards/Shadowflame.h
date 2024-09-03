#ifndef SHADOWFLAME_H
#define SHADOWFLAME_H

#include "logic/cards/SingleArgTargetFriendlyCard.h"

struct Shadowflame: public SingleArgTargetFriendlyCard
{
    Shadowflame(): SingleArgTargetFriendlyCard("Shadowflame", 4) {}

    CLONE

    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) override;
};

#endif