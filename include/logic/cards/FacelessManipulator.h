#ifndef FACELESS_MANIPULATOR_H
#define FACELESS_MANIPULATOR_H

#include "logic/cards/Card.h"

struct FacelessManipulator: public Card
{
    FacelessManipulator(): Card("Faceless Manipulator", 5, 3, 3) {}

    void on_play(Game& game, std::vector<OnPlayArg> args) override;
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position) override;
};

#endif