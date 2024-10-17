#ifndef DEFENDER_OF_ARGUS_H
#define DEFENDER_OF_ARGUS_H

#include "logic/cards/SingleArgSelfPlayPositionCard.h"

class DefenderOfArgus: public SingleArgSelfPlayPositionCard
{
private:
    DefenderOfArgus(): SingleArgSelfPlayPositionCard("Defender of Argus", 4, 2, 3) {}
public:
    static const DefenderOfArgus instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
};

inline const DefenderOfArgus DefenderOfArgus::instance;

#endif