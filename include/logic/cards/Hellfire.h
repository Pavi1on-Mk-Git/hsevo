#ifndef HELLFIRE_H
#define HELLFIRE_H

#include "logic/cards/Card.h"

struct Hellfire: public Card
{
    Hellfire(): Card("Hellfire", 4) {}

    CLONE_CARD

    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) override;
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position) override;
};

#endif