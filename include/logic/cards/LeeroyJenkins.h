#ifndef LEEROY_JENKINS_H
#define LEEROY_JENKINS_H

#include "logic/cards/MinionCard.h"

class LeeroyJenkins: public MinionCard
{
private:
    LeeroyJenkins(): MinionCard("Leeroy Jenkins", 4, 6, 2, CHARGE) {}
public:
    static const LeeroyJenkins instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
};

inline const LeeroyJenkins LeeroyJenkins::instance;


#endif