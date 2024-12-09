#include "players/RandomPlayerLogic.h"

#include "logic/Game.h"

RandomPlayerLogic::RandomPlayerLogic(const Decklist& decklist, Rng& rng): PlayerLogic(decklist), rng_(rng) {}

Game RandomPlayerLogic::choose_and_apply_action(const Game& game, const std::vector<std::unique_ptr<Action>>& actions)
    const
{
    auto& action = actions.at(rng_.uniform_int(0, actions.size() - 1));

    auto new_states = action->apply(game);

    return new_states.at(rng_.uniform_int(0, new_states.size() - 1));
}