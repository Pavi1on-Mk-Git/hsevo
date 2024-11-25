#include "logic/cards/CairneBloodhoof.h"

#include "logic/Game.h"
#include "logic/cards/BaineBloodhoof.h"

std::vector<Game> CairneBloodhoof::on_death(const Game& prev_state, unsigned player_id) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    game.add_minion(&BaineBloodhoof::instance, game.players.at(player_id).board.minion_count(), player_id);

    return resulting_states;
}