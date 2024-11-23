#include "logic/cards/Brawl.h"

#include "logic/Game.h"

std::vector<Game> Brawl::on_play(Game& game, const std::vector<OnPlayArg>&) const
{
    std::vector<Game> resulting_states;

    const unsigned current_minion_count = game.current_player().board.minion_count();
    const unsigned opponent_minion_count = game.opponent().board.minion_count();

    for(unsigned survivor_position = 0; survivor_position < current_minion_count; ++survivor_position)
    {
        Game game_copy(game);

        for(unsigned board_position = 0; board_position < current_minion_count; ++board_position)
        {
            if(survivor_position == board_position)
                continue;

            game_copy.current_player().board.get_minion(board_position).health = 0;
        }

        for(unsigned board_position = 0; board_position < opponent_minion_count; ++board_position)
        {
            game_copy.opponent().board.get_minion(board_position).health = 0;
        }

        resulting_states.push_back(game_copy);
    }

    for(unsigned survivor_position = 0; survivor_position < opponent_minion_count; ++survivor_position)
    {
        Game game_copy(game);

        for(unsigned board_position = 0; board_position < opponent_minion_count; ++board_position)
        {
            if(survivor_position == board_position)
                continue;

            game_copy.opponent().board.get_minion(board_position).health = 0;
        }

        for(unsigned board_position = 0; board_position < current_minion_count; ++board_position)
        {
            game_copy.current_player().board.get_minion(board_position).health = 0;
        }

        resulting_states.push_back(game_copy);
    }

    if(resulting_states.empty())
        return {game};

    return resulting_states;
}
