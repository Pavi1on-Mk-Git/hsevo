#include "logic/cards/CairneBloodhoof.h"

#include "logic/Game.h"
#include "logic/cards/BaineBloodhoof.h"

std::vector<Game> CairneBloodhoof::on_death(Game& game, unsigned player_id) const
{
    game.add_minion(&BaineBloodhoof::instance, game.players.at(player_id).board.minion_count(), player_id);

    return {game};
}