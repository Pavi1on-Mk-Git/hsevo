#ifndef SUNFURY_PROTECTOR_H
#define SUNFURY_PROTECTOR_H

#include "logic/cards/SingleArgSelfPlayPositionCard.h"

struct SunfuryProtector: public SingleArgSelfPlayPositionCard
{
    SunfuryProtector(): SingleArgSelfPlayPositionCard("Sunfury Protector", 2, 2, 3) {}

    CLONE_CARD

    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) override;
};


#endif