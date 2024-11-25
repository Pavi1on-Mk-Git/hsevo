#include "logic/cards/BaronGeddon.h"

#include "logic/Game.h"

const unsigned BARON_GEDDON_EOT_DMG = 2;

std::vector<Game> BaronGeddon::on_end_of_turn(const Game& prev_state, unsigned id) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    auto deal_dmg = [&game](Entity& entity) { entity.deal_dmg(BARON_GEDDON_EOT_DMG, game); };

    for(auto& minion: game.current_player().board)
    {
        if(minion.id == id)
            continue;
        deal_dmg(minion);
    }

    for(auto& minion: game.opponent().board)
        deal_dmg(minion);

    deal_dmg(*game.current_player().hero);
    deal_dmg(*game.opponent().hero);

    return resulting_states;
}