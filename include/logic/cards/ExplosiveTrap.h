#ifndef EXPLOSIVE_TRAP_H
#define EXPLOSIVE_TRAP_H

#include "logic/cards/SecretCard.h"

class ExplosiveTrap: public SecretCard
{
private:
    ExplosiveTrap(): SecretCard("Explosive Trap", 2) {}
public:
    static const ExplosiveTrap instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
    SecretResult on_trigger(Game& game, const FightAction& action) const override;
};

inline const ExplosiveTrap ExplosiveTrap::instance;

#endif
