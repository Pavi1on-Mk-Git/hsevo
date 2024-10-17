#ifndef HELLFIRE_H
#define HELLFIRE_H

#include "logic/cards/Card.h"

class Hellfire: public Card
{
private:
    Hellfire(): Card("Hellfire", 4) {}
public:
    static const Hellfire instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
};

inline const Hellfire Hellfire::instance;

#endif