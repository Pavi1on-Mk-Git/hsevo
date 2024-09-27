#include "logic/cards/Shadowflame.h"

#include "logic/Game.h"

std::vector<Game> Shadowflame::on_play(Game& game, const std::vector<OnPlayArg>& args)
{
    const auto target_position = std::get<unsigned>(args.at(0));

    auto& chosen_minion = game.current_player().board.get_minion(target_position);

    unsigned dmg_to_deal = chosen_minion.attack;
    chosen_minion.health = 0;

    auto& opponent_board = game.opponent().board;

    for(unsigned enemy_position = 0; enemy_position < opponent_board.minion_count(); ++enemy_position)
        opponent_board.get_minion(enemy_position).health -= dmg_to_deal;

    return {game};
}