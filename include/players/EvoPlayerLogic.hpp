#ifndef EVO_PLAYER_LOGIC_H
#define EVO_PLAYER_LOGIC_H

#include <algorithm>

#include "logic/Game.h"
#include "players/PlayerLogic.h"
#include "utils/Rng.h"

/**
 * Logic of a player using an evolutionary algorithm to make its decisions
 */
template <typename Evo>
class EvoPlayerLogic: public PlayerLogic
{
private:
    /**
     * Source of randomness
     */
    Rng& rng_;
public:
    /**
     * Instance of evolutionary algorithm specimen used for decision-making
     */
    Evo evo;

    /**
     * Construct a player logic
     * @param decklist Decklist used by the player
     * @param evo Internal evolutionary algorithm specimen
     * @param rng Source of randomness
     */
    EvoPlayerLogic(const Decklist& decklist, Evo evo, Rng& rng): PlayerLogic(decklist), rng_(rng), evo(evo) {}

    /**
     * Construct a player logic
     * @param decklist Decklist used
     * @param in Stream containing evolutionary algorithm specimen data
     * @param rng Source of randomness
     */
    EvoPlayerLogic(const Decklist& decklist, std::istream& in, Rng& rng): PlayerLogic(decklist), rng_(rng), evo(in) {}

    /**
     * Score provided game state and add it to the current score
     * @param sum Current score sum
     * @param game Game state to score
     * @return Sum of the scores
     */
    double add_game_score(double sum, const Game& game) const
    {
        auto inputs = game.get_state().get_evo_input();
        return sum + evo.score_vec(inputs.at(0)) - evo.score_vec(inputs.at(1));
    }

    /**
     * Compute average score for the provided vector of states
     * @param states Vector of states
     * @return Average score
     */
    double average_of_states(const std::vector<Game>& states) const
    {
        return std::ranges::fold_left(
                   states, 0., [this](double sum, const Game& game) { return add_game_score(sum, game); }
               ) /
               states.size();
    }

    Game choose_and_apply_action(const Game& game, const std::vector<std::unique_ptr<Action>>& actions) const override
    {
        std::vector<std::vector<Game>> states_for_action;
        states_for_action.reserve(actions.size());

        std::ranges::transform(
            actions, std::back_inserter(states_for_action),
            [&game](const std::unique_ptr<Action>& action) { return action->test_apply(game); }
        );

        unsigned best_action_id = std::ranges::max_element(
                                      states_for_action,
                                      [this](
                                          const std::vector<Game>& first_states, const std::vector<Game>& second_states
                                      ) { return average_of_states(first_states) < average_of_states(second_states); }
                                  ) -
                                  states_for_action.begin();

        auto resulting_states = actions.at(best_action_id)->apply(game);

        return resulting_states.at(rng_.uniform_int(0, resulting_states.size() - 1));
    }
};

#endif