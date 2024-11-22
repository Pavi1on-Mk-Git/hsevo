#ifndef SHIELD_BLOCK_H
#define SHIELD_BLOCK_H

#include "logic/cards/Card.h"

class ShieldBlock: public Card
{
private:
    ShieldBlock(): Card("Shield Block", 3) {}
public:
    static const ShieldBlock instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
};

inline const ShieldBlock ShieldBlock::instance;


#endif