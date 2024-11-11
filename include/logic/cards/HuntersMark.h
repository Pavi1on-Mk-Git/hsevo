#ifndef HUNTERS_MARK_H
#define HUNTERS_MARK_H

#include "logic/cards/SingleArgTargetMinionCard.h"

class HuntersMark: public SingleArgTargetMinionCard
{
private:
    HuntersMark(): SingleArgTargetMinionCard("Hunter's Mark", 0) {}
public:
    static const HuntersMark instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
};

inline const HuntersMark HuntersMark::instance;

#endif