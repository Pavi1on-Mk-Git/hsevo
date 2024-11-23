#include "logic/cards/SylvanasWindrunner.h"

#include "logic/Game.h"

std::vector<Game> SylvanasWindrunner::on_death(Game& game, unsigned player_id) const
{
    std::vector<Game> post_steal_states;

    for(unsigned opponent_position = 0; opponent_position < game.players.at(1 - player_id).board.minion_count();
        ++opponent_position)
    {
        Game game_copy(game);

        game_copy.change_minion_side(1 - player_id, opponent_position);

        post_steal_states.push_back(game_copy);
    }

    return post_steal_states;
}
