#ifndef SLAM_H
#define SLAM_H

#include "logic/cards/SingleArgTargetMinionCard.h"

class Slam: public SingleArgTargetMinionCard
{
private:
    Slam(): SingleArgTargetMinionCard("Slam", 2) {}
public:
    static const Slam instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
};

inline const Slam Slam::instance;

#endif