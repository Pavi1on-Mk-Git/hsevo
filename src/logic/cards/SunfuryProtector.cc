#include "logic/cards/SunfuryProtector.h"

#include "logic/Game.h"

std::vector<Game> SunfuryProtector::on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    const auto position_played = std::get<unsigned>(args.at(0));

    std::vector<unsigned> neighbour_positions;

    if(position_played >= 1)
        neighbour_positions.push_back(position_played - 1);
    if(position_played + 1 < game.current_player().board.minion_count())
        neighbour_positions.push_back(position_played + 1);

    for(unsigned board_position: neighbour_positions)
        game.current_player().board.get_minion(board_position).keywords |= TAUNT;

    return resulting_states;
}