#ifndef FIGHT_ACTION_H
#define FIGHT_ACTION_H

#include <optional>

#include "logic/Action.h"
#include "logic/TargetType.h"

/**
 * Action of choosing two entities to fight
 */
struct FightAction: Action
{
    /**
     * Attacker and defender of the fight
     */
    TargetType attacker, defender;

    /**
     * Positions of the attacker and defender
     *
     * Hero-type entities don't need a position to fight
     */
    std::optional<unsigned> attacker_position, defender_position;

    /**
     * Construct a fight action between two minions
     * @param attacker Should be a minion
     * @param attacker_position Position of the attacker
     * @param defender Should be a minion
     * @param defender_position Position of the defender
     */
    FightAction(
        const TargetType& attacker, unsigned attacker_position, const TargetType& defender, unsigned defender_position
    );

    /**
     * Construct a fight action between a hero and a minion
     * @param attacker Should be a hero
     * @param defender Should be a minion
     * @param defender_position Position of the defender
     */
    FightAction(const TargetType& attacker, const TargetType& defender, unsigned defender_position);

    /**
     * Construct a fight action between a minion and a hero
     * @param attacker Should be a minion
     * @param attacker_position Position of the attacker
     * @param defender Should be a hero
     */
    FightAction(const TargetType& attacker, unsigned attacker_position, const TargetType& defender);

    /**
     * Construct a fight action between two heroes
     * @param attacker Should be a hero
     * @param defender Should be a hero
     */
    FightAction(const TargetType& attacker, const TargetType& defender);
    std::vector<Game> apply(const Game& game) const override;
    std::vector<Game> test_apply(const Game& game) const override;
    std::deque<GuiElementId> element_sequence() const override;
};

#endif