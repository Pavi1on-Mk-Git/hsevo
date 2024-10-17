#ifndef LORD_JARAXXUS_CARD_H
#define LORD_JARAXXUS_CARD_H

#include "logic/cards/Card.h"

class LordJaraxxusCard: public Card
{
private:
    LordJaraxxusCard(): Card("Lord Jaraxxus", 9) {}
public:
    static const LordJaraxxusCard instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
};

inline const LordJaraxxusCard LordJaraxxusCard::instance;

#endif