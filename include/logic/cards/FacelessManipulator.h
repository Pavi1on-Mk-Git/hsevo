#ifndef FACELESS_MANIPULATOR_H
#define FACELESS_MANIPULATOR_H

#include "logic/cards/MinionCard.h"

class FacelessManipulator: public MinionCard
{
private:
    FacelessManipulator(): MinionCard("Faceless Manipulator", 5, 3, 3) {}
public:
    static const FacelessManipulator instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position)
        const override;
};

inline const FacelessManipulator FacelessManipulator::instance;

#endif