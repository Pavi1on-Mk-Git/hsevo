#ifndef POWER_OVERWHELMING_H
#define POWER_OVERWHELMING_H

#include "logic/cards/SingleArgTargetFriendlyMinionCard.h"

class PowerOverwhelming: public SingleArgTargetFriendlyMinionCard
{
private:
    PowerOverwhelming(): SingleArgTargetFriendlyMinionCard("Power Overwhelming", 1) {}
public:
    static const PowerOverwhelming instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
};

inline const PowerOverwhelming PowerOverwhelming::instance;

#endif