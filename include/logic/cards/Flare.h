#ifndef FLARE_H
#define FLARE_H

#include "logic/cards/Card.h"

class Flare: public Card
{
private:
    Flare(): Card("Flare", 1) {}
public:
    static const Flare instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
};

inline const Flare Flare::instance;

#endif