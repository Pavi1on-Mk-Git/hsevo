#ifndef LORD_JARAXXUS_CARD_H
#define LORD_JARAXXUS_CARD_H

#include "logic/cards/Card.h"

struct LordJaraxxusCard: public Card
{
    LordJaraxxusCard(): Card("Lord Jaraxxus", 9) {}

    CLONE_CARD

    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) override;
};

#endif