#ifndef SUNFURY_PROTECTOR_H
#define SUNFURY_PROTECTOR_H

#include "logic/cards/SingleArgSelfPlayPositionMinionCard.h"

class SunfuryProtector: public SingleArgSelfPlayPositionMinionCard
{
private:
    SunfuryProtector(): SingleArgSelfPlayPositionMinionCard("Sunfury Protector", 2, 2, 3) {}
public:
    static const SunfuryProtector instance;
    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;
};

inline const SunfuryProtector SunfuryProtector::instance;


#endif