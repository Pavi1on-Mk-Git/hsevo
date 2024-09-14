#ifndef TWILIGHT_DRAKE_H
#define TWILIGHT_DRAKE_H

#include "logic/cards/SingleArgSelfPlayPositionCard.h"

struct TwilightDrake: public SingleArgSelfPlayPositionCard
{
    TwilightDrake(): SingleArgSelfPlayPositionCard("Twilight Drake", 4, 4, 1, Tribe::DRAGON) {}

    CLONE_CARD

    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) override;
};

#endif