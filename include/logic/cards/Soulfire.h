#ifndef SOULFIRE_H
#define SOULFIRE_H

#include "logic/cards/SingleArgTargetCard.h"

class Soulfire: public SingleArgTargetCard
{
private:
    Soulfire(): SingleArgTargetCard("Soulfire", 0) {}
public:
    static const Soulfire instance;
    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;
};

inline const Soulfire Soulfire::instance;

#endif