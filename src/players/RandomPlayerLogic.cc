#include "players/RandomPlayerLogic.h"

#include "logic/Game.h"
#include "utils/Rng.h"

RandomPlayerLogic::RandomPlayerLogic(const Decklist& decklist): PlayerLogic(decklist) {}

Game RandomPlayerLogic::choose_and_apply_action(const Game& game, const std::vector<std::unique_ptr<Action>>& actions)
    const
{
    auto& action = actions.at(Rng::instance().uniform_int(0, actions.size() - 1));

    auto new_states = action->apply(game);

    return new_states.at(Rng::instance().uniform_int(0, new_states.size() - 1));
}