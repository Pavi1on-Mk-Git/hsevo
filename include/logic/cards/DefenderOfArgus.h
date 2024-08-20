#ifndef DEFENDER_OF_ARGUS_H
#define DEFENDER_OF_ARGUS_H

#include "logic/cards/SingleArgSelfPlayPositionCard.h"

struct DefenderOfArgus: public SingleArgSelfPlayPositionCard
{
    DefenderOfArgus(): SingleArgSelfPlayPositionCard("Defender of Argus", 4, 2, 3) {}

    void on_play(Game& game, std::vector<OnPlayArg> args) override;
};

#endif