#ifndef SECRET_CARD_H
#define SECRET_CARD_H

#include <ranges>

#include "logic/FightAction.h"
#include "logic/cards/Card.h"

/**
 * Result of a secret getting triggered
 */
struct SecretResult
{
    /**
     * Resulting new game states and fight actions
     */
    std::vector<std::pair<Game, FightAction>> new_states_and_actions;

    /**
     * Flag signaling if the actions can be continued after the secret has triggered
     */
    bool can_continue;

    /**
     * Construct a secret result
     * @param new_states Resulting game states
     * @param new_actions Modified action for each resulting game state
     * @param can_continue Flag signaling if the actions can be continued
     */
    SecretResult(const std::vector<Game>& new_states, const std::vector<FightAction>& new_actions, bool can_continue);
};

/**
 * Base card for all cards representing a secret-type spell
 */
class SecretCard: public Card
{
protected:
    using Card::Card;
public:
    virtual ~SecretCard() = default;

    /**
     * Calculate if the secret has activated after the provided action and if so return a result from this secret
     * getting triggered
     * @param prev_state Previous game state
     * @param action Action which could have triggered the secret
     * @return Result of the secret getting trigered or `std::nullopt` if it hasn't been triggered
     */
    virtual std::optional<SecretResult> on_trigger(const Game& prev_state, const FightAction& action) const = 0;
};

#endif
