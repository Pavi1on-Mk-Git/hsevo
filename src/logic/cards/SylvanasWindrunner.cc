#include "logic/cards/SylvanasWindrunner.h"

#include "logic/Game.h"

std::vector<Game> SylvanasWindrunner::on_death(const Game& prev_state, unsigned player_id) const
{
    std::vector<Game> post_steal_states;

    for(unsigned opponent_position = 0; opponent_position < prev_state.players.at(1 - player_id).board.minion_count();
        ++opponent_position)
    {
        Game game_copy(prev_state);

        game_copy.change_minion_side(1 - player_id, opponent_position);

        post_steal_states.push_back(game_copy);
    }

    if(post_steal_states.empty())
        return {prev_state};

    return post_steal_states;
}
