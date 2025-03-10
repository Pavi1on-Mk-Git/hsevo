#include "logic/cards/Shadowflame.h"

#include "logic/Game.h"

std::vector<Game> Shadowflame::on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    const auto target_position = std::get<unsigned>(args.at(1));

    auto& chosen_minion = game.current_player().board.get_minion(target_position);

    unsigned dmg_to_deal = chosen_minion.attack;
    chosen_minion.health = 0;

    for(auto& opponent_minion: game.opponent().board)
        opponent_minion.deal_dmg(dmg_to_deal + game.current_player().spell_damage, game);

    return resulting_states;
}