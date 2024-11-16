#ifndef FREEZING_TRAP_H
#define FREEZING_TRAP_H

#include "logic/cards/SecretCard.h"

class FreezingTrap: public SecretCard
{
private:
    FreezingTrap(): SecretCard("Freezing Trap", 2) {}
public:
    static const FreezingTrap instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
    SecretResult on_trigger(Game& game, const FightAction& action) const override;
};

inline const FreezingTrap FreezingTrap::instance;

#endif
