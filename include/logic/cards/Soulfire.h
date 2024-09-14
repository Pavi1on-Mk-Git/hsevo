#ifndef SOULFIRE_H
#define SOULFIRE_H

#include "logic/cards/SingleArgTargetCard.h"

struct Soulfire: public SingleArgTargetCard
{
    Soulfire(): SingleArgTargetCard("Soulfire", 0) {}

    CLONE_CARD

    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) override;
};

#endif