#ifndef SACRIFICIAL_PACT_H
#define SACRIFICIAL_PACT_H

#include "logic/cards/Card.h"

struct SacrificialPact: public Card
{
    SacrificialPact(): Card("Sacrificial Pact", 0) {}

    CLONE

    void on_play(Game& game, const std::vector<OnPlayArg>& args) override;
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position) override;
};

#endif