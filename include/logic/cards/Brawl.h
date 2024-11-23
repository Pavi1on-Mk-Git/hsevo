#ifndef BRAWL_H
#define BRAWL_H

#include "logic/cards/Card.h"

class Brawl: public Card
{
private:
    Brawl(): Card("Brawl", 5) {}
public:
    static const Brawl instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
};

inline const Brawl Brawl::instance;

#endif