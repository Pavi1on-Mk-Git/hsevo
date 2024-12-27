#ifndef DEFENDER_OF_ARGUS_H
#define DEFENDER_OF_ARGUS_H

#include "logic/cards/SingleArgSelfPlayPositionMinionCard.h"

class DefenderOfArgus: public SingleArgSelfPlayPositionMinionCard
{
private:
    DefenderOfArgus(): SingleArgSelfPlayPositionMinionCard("Defender of Argus", 4, 2, 3) {}
public:
    static const DefenderOfArgus instance;
    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;
};

inline const DefenderOfArgus DefenderOfArgus::instance;

#endif