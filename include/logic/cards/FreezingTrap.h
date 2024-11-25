#ifndef FREEZING_TRAP_H
#define FREEZING_TRAP_H

#include "logic/cards/SecretCard.h"

class FreezingTrap: public SecretCard
{
private:
    FreezingTrap(): SecretCard("Freezing Trap", 2) {}
public:
    static const FreezingTrap instance;
    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;
    SecretResult on_trigger(const Game& prev_state, const FightAction& action) const override;
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position)
        const override;
};

inline const FreezingTrap FreezingTrap::instance;

#endif
