#include "players/EvoPlayerLogic.h"

#include <algorithm>

#include "logic/Game.h"

EvoPlayerLogic::EvoPlayerLogic(const DeckList& decklist, SimpleEvo<1 + 2 * Board::MAX_BOARD_SIZE + 3> evo):
    PlayerLogic(decklist), evo(evo)
{}

std::unique_ptr<Action> EvoPlayerLogic::choose_action(const Game& game, std::vector<std::unique_ptr<Action>> actions)
    const
{
    std::vector<double> action_scores;
    for(const auto& action: actions)
    {
        Game game_copy = game.copy();
        action->apply(game_copy);

        auto inputs = game_copy.get_state().get_evo_input();
        action_scores.push_back(evo.score_vec(inputs.at(0)) - evo.score_vec(inputs.at(1)));
    }

    auto best_element_index = std::distance(
        action_scores.begin(), std::max_element(action_scores.begin(), action_scores.end())
    );

    return std::move(actions.at(best_element_index));
}