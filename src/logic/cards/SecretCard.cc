#include "logic/cards/SecretCard.h"

#include <ranges>

#include "logic/Game.h"

SecretResult::SecretResult(
    const std::vector<Game>& new_states, const std::vector<FightAction>& new_actions, bool can_continue
): triggered(true), can_continue(can_continue)
{
    for(auto [state, action]: std::views::zip(new_states, new_actions))
        new_states_and_actions.emplace_back(state, action);
}

SecretResult::SecretResult(): triggered(false) {}
