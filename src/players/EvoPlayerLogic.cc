#include "players/EvoPlayerLogic.h"

#include <algorithm>

#include "logic/Game.h"

EvoPlayerLogic::EvoPlayerLogic(const Decklist& decklist, SimpleEvo<1 + 2 * Board::MAX_BOARD_SIZE + 3> evo):
    PlayerLogic(decklist), evo(evo)
{}

double EvoPlayerLogic::add_game_score(double sum, const Game& game) const
{
    auto inputs = game.get_state().get_evo_input();
    return sum + evo.score_vec(inputs.at(0)) - evo.score_vec(inputs.at(1));
}

double EvoPlayerLogic::average_of_states(const std::vector<Game>& states) const
{
    return std::accumulate(
               states.begin(), states.end(), 0.,
               [this](double sum, const Game& game) { return add_game_score(sum, game); }
           ) /
           states.size();
}

Game EvoPlayerLogic::choose_and_apply_action(Game& game, std::vector<std::unique_ptr<Action>> actions) const
{
    std::vector<std::vector<Game>> states_for_action;

    std::transform(
        actions.begin(), actions.end(), std::back_inserter(states_for_action),
        [&game](const std::unique_ptr<Action>& action) {
            Game game_copy(game);
            return action->apply(game_copy);
        }
    );

    auto best_action = std::max_element(
        states_for_action.begin(), states_for_action.end(),
        [this](const std::vector<Game>& first_states, const std::vector<Game>& second_states) {
            return average_of_states(first_states) < average_of_states(second_states);
        }
    );

    return best_action->at(Rng::instance()->uniform_int(0, best_action->size() - 1));
}