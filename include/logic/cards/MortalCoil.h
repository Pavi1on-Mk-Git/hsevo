#ifndef MORTAL_COIL_H
#define MORTAL_COIL_H

#include "logic/cards/SingleArgTargetCard.h"

struct MortalCoil: public SingleArgTargetCard
{
    MortalCoil(): SingleArgTargetCard("Mortal Coil", 1) {}

    CLONE

    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) override;
};

#endif