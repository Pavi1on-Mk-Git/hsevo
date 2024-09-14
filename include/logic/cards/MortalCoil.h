#ifndef MORTAL_COIL_H
#define MORTAL_COIL_H

#include "logic/cards/SingleArgTargetMinionCard.h"

struct MortalCoil: public SingleArgTargetMinionCard
{
    MortalCoil(): SingleArgTargetMinionCard("Mortal Coil", 1) {}

    CLONE_CARD

    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) override;
};

#endif