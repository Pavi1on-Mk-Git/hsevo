#ifndef COIN_H
#define COIN_H

#include "logic/cards/Card.h"

struct Coin: public Card
{
    Coin(): Card("The Coin", 0) {}

    CLONE_CARD

    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) override;
};

#endif