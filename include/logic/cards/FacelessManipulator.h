#ifndef FACELESS_MANIPULATOR_H
#define FACELESS_MANIPULATOR_H

#include "logic/cards/MinionCard.h"

struct FacelessManipulator: public MinionCard
{
    FacelessManipulator(): MinionCard("Faceless Manipulator", 5, 3, 3) {}

    CLONE

    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) override;
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position) override;
};

#endif