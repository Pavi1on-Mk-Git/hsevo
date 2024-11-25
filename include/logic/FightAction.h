#ifndef FIGHT_ACTION_H
#define FIGHT_ACTION_H

#include <optional>

#include "logic/Action.h"
#include "logic/TargetType.h"

struct FightAction: Action
{
    TargetType attacker, defender;
    std::optional<unsigned> attacker_position, defender_position;

    FightAction(
        const TargetType& attacker, unsigned attacker_position, const TargetType& defender, unsigned defender_position
    );
    FightAction(const TargetType& attacker, const TargetType& defender, unsigned defender_position);
    FightAction(const TargetType& attacker, unsigned attacker_position, const TargetType& defender);
    FightAction(const TargetType& attacker, const TargetType& defender);
    std::vector<Game> apply(const Game& game) const override;
    std::vector<Game> test_apply(const Game& game) const override;
    std::deque<GuiElementId> element_sequence() const override;
};

#endif