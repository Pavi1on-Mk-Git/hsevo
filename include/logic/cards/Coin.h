#ifndef COIN_H
#define COIN_H

#include "logic/cards/Card.h"

class Coin: public Card
{
private:
    Coin(): Card("The Coin", 0) {}
public:
    static const Coin instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
};

inline const Coin Coin::instance;

#endif