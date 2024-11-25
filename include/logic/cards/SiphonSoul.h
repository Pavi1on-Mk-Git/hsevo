#ifndef SIPHON_SOUL_H
#define SIPHON_SOUL_H

#include "logic/cards/SingleArgTargetMinionCard.h"

class SiphonSoul: public SingleArgTargetMinionCard
{
private:
    SiphonSoul(): SingleArgTargetMinionCard("Siphon Soul", 6) {}
public:
    static const SiphonSoul instance;
    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;
};

inline const SiphonSoul SiphonSoul::instance;

#endif