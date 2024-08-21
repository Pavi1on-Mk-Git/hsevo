#ifndef SUNFURY_PROTECTOR_H
#define SUNFURY_PROTECTOR_H

#include "logic/cards/SingleArgSelfPlayPositionCard.h"

struct SunfuryProtector: public SingleArgSelfPlayPositionCard
{
    SunfuryProtector(): SingleArgSelfPlayPositionCard("Sunfury Protector", 2, 2, 3) {}

    CLONE

    void on_play(Game& game, std::vector<OnPlayArg> args) override;
};


#endif