#ifndef WHIRLWIND_H
#define WHIRLWIND_H

#include "logic/cards/Card.h"

class Whirlwind: public Card
{
private:
    Whirlwind(): Card("Whirlwind", 1) {}
public:
    static const Whirlwind instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
};

inline const Whirlwind Whirlwind::instance;

#endif