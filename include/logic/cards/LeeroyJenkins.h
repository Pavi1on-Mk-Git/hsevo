#ifndef LEEROY_JENKINS_H
#define LEEROY_JENKINS_H

#include "logic/cards/MinionCard.h"

struct LeeroyJenkins: public MinionCard
{
    LeeroyJenkins(): MinionCard("Leeroy Jenkins", 4, 6, 2, CHARGE) {}

    CLONE

    void on_play(Game& game, std::vector<OnPlayArg> args) override;
};


#endif