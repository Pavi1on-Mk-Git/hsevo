#ifndef TWILIGHT_DRAKE_H
#define TWILIGHT_DRAKE_H

#include "logic/cards/SingleArgSelfPlayPositionMinionCard.h"

class TwilightDrake: public SingleArgSelfPlayPositionMinionCard
{
private:
    TwilightDrake(): SingleArgSelfPlayPositionMinionCard("Twilight Drake", 4, 4, 1, Tribe::DRAGON) {}
public:
    static const TwilightDrake instance;
    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;
};

inline const TwilightDrake TwilightDrake::instance;

#endif