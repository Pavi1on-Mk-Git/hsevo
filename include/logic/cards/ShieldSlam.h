#ifndef SHIELD_SLAM_H
#define SHIELD_SLAM_H

#include "logic/cards/SingleArgTargetMinionCard.h"

class ShieldSlam: public SingleArgTargetMinionCard
{
private:
    ShieldSlam(): SingleArgTargetMinionCard("Shield Slam", 1) {}
public:
    static const ShieldSlam instance;
    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;
};

inline const ShieldSlam ShieldSlam::instance;

#endif