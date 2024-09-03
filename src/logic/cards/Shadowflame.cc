#include "logic/cards/Shadowflame.h"

#include "logic/Game.h"

const unsigned SHADOWFLAME_DMG = 4;

std::vector<Game> Shadowflame::on_play(Game& game, const std::vector<OnPlayArg>& args)
{
    const auto target_position = std::get<unsigned>(args.at(0));

    game.current_player().hero.board.get_minion(target_position).health = 0;

    auto& opponent_board = game.opponent().hero.board;

    for(unsigned enemy_position = 0; enemy_position < opponent_board.minion_count(); ++enemy_position)
        opponent_board.get_minion(enemy_position).health -= SHADOWFLAME_DMG;

    return {game};
}