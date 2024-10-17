#ifndef SUNFURY_PROTECTOR_H
#define SUNFURY_PROTECTOR_H

#include "logic/cards/SingleArgSelfPlayPositionCard.h"

class SunfuryProtector: public SingleArgSelfPlayPositionCard
{
private:
    SunfuryProtector(): SingleArgSelfPlayPositionCard("Sunfury Protector", 2, 2, 3) {}
public:
    static const SunfuryProtector instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
};

inline const SunfuryProtector SunfuryProtector::instance;


#endif