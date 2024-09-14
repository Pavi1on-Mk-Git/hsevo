#ifndef SIPHON_SOUL_H
#define SIPHON_SOUL_H

#include "logic/cards/SingleArgTargetMinionCard.h"

struct SiphonSoul: public SingleArgTargetMinionCard
{
    SiphonSoul(): SingleArgTargetMinionCard("Siphon Soul", 6) {}

    CLONE_CARD

    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) override;
};

#endif