#ifndef UNLEASH_THE_HOUNDS_H
#define UNLEASH_THE_HOUNDS_H

#include "logic/cards/Card.h"

class UnleashTheHounds: public Card
{
private:
    UnleashTheHounds(): Card("Unleash The Hounds", 3) {}
public:
    static const UnleashTheHounds instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
};

inline const UnleashTheHounds UnleashTheHounds::instance;

#endif