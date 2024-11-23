#include "logic/cards/BaronGeddon.h"

#include "logic/Game.h"

const unsigned BARON_GEDDON_EOT_DMG = 2;

std::vector<Game> BaronGeddon::on_end_of_turn(Game& game, unsigned id, unsigned player_id) const
{
    auto deal_dmg = [&game](Entity& entity) { entity.deal_dmg(BARON_GEDDON_EOT_DMG, game); };

    for(auto& minion: game.players.at(player_id).board)
    {
        if(minion.id == id)
            continue;
        deal_dmg(minion);
    }

    for(auto& minion: game.players.at(1 - player_id).board)
        deal_dmg(minion);

    deal_dmg(*game.current_player().hero);
    deal_dmg(*game.opponent().hero);

    return {game};
}