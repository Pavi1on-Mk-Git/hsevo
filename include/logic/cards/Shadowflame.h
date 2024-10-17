#ifndef SHADOWFLAME_H
#define SHADOWFLAME_H

#include "logic/cards/SingleArgTargetFriendlyMinionCard.h"

class Shadowflame: public SingleArgTargetFriendlyMinionCard
{
private:
    Shadowflame(): SingleArgTargetFriendlyMinionCard("Shadowflame", 4) {}
public:
    static const Shadowflame instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
};

inline const Shadowflame Shadowflame::instance;

#endif