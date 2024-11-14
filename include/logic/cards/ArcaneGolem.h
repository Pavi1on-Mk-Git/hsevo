#ifndef ARCANE_GOLEM_H
#define ARCANE_GOLEM_H

#include "logic/cards/MinionCard.h"

class ArcaneGolem: public MinionCard
{
private:
    ArcaneGolem(): MinionCard("Arcane Golem", 3, 4, 2, MinionKeywords::CHARGE) {}
public:
    static const ArcaneGolem instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
};

inline const ArcaneGolem ArcaneGolem::instance;

#endif