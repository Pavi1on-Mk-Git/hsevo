#ifndef TWILIGHT_DRAKE_H
#define TWILIGHT_DRAKE_H

#include "logic/cards/SingleArgSelfPlayPositionCard.h"

struct TwilightDrake: public SingleArgSelfPlayPositionCard
{
    TwilightDrake(): SingleArgSelfPlayPositionCard("Twilight Drake", 4, 4, 1) {}

    void on_play(Game& game, std::vector<OnPlayArg> args) override;
};

#endif