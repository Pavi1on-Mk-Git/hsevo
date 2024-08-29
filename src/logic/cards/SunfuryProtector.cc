#include "logic/cards/SunfuryProtector.h"

#include "logic/Game.h"

void SunfuryProtector::on_play(Game& game, const std::vector<OnPlayArg>& args)
{
    const auto position_played = std::get<unsigned>(args.at(0));

    std::vector<unsigned> neighbour_positions;

    if(position_played >= 1)
        neighbour_positions.push_back(position_played - 1);
    if(position_played + 1 < game.current_player().hero.board.minion_count())
        neighbour_positions.push_back(position_played + 1);

    for(unsigned board_position: neighbour_positions)
        game.current_player().hero.board.get_minion(board_position).keywords |= TAUNT;
}