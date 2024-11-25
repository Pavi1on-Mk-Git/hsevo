#include "logic/cards/RagnarosTheFirelord.h"

#include "logic/Game.h"

const unsigned RAGNAROS_EOT_DMG = 8;

std::vector<Game> RagnarosTheFirelord::on_end_of_turn(const Game& prev_state, unsigned) const
{
    std::vector<Game> post_eot_states;

    Game game_copy(prev_state);
    game_copy.opponent().hero->deal_dmg(RAGNAROS_EOT_DMG, game_copy);
    post_eot_states.push_back(game_copy);

    for(unsigned target_position = 0; target_position < prev_state.opponent().board.minion_count(); ++target_position)
    {
        Game game_copy(prev_state);
        game_copy.opponent().board.get_minion(target_position).deal_dmg(RAGNAROS_EOT_DMG, game_copy);
        post_eot_states.push_back(game_copy);
    }

    return post_eot_states;
}