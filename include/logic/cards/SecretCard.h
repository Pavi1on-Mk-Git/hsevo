#ifndef SECRET_CARD_H
#define SECRET_CARD_H

#include <ranges>

#include "logic/FightAction.h"
#include "logic/cards/Card.h"

struct SecretResult
{
    std::vector<std::pair<Game, FightAction>> new_states_and_actions;
    bool can_continue;

    SecretResult(const std::vector<Game>& new_states, const std::vector<FightAction>& new_actions, bool can_continue);
};

class SecretCard: public Card
{
protected:
    using Card::Card;
public:
    virtual ~SecretCard() = default;
    virtual std::optional<SecretResult> on_trigger(const Game& prev_state, const FightAction& action) const = 0;
};

#endif
