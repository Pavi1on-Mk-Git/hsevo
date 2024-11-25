#ifndef ABUSIVE_SERGEANT_H
#define ABUSIVE_SERGEANT_H

#include "logic/cards/SingleArgTargetMinionMinionCard.h"

class AbusiveSergeant: public SingleArgTargetMinionMinionCard
{
private:
    AbusiveSergeant(): SingleArgTargetMinionMinionCard("Abusive Sergeant", 1, 2, 1) {}
public:
    static const AbusiveSergeant instance;
    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;
};

inline const AbusiveSergeant AbusiveSergeant::instance;

#endif