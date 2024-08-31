#include "logic/cards/FacelessManipulator.h"

#include "logic/Game.h"

std::vector<Game> FacelessManipulator::on_play(Game& game, const std::vector<OnPlayArg>& args)
{
    const auto position_played = std::get<unsigned>(args[0]);
    const auto target_position = std::get<unsigned>(args[1]);

    auto& board = game.current_player().hero.board;

    auto target_copy = board.get_minion(target_position);

    board.transform_minion(target_copy, position_played);

    return {game};
}

std::vector<std::unique_ptr<PlayCardAction>> FacelessManipulator::create_play_actions(
    const Game& game, unsigned hand_position
)
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned current_minion_count = game.current_player().hero.board.minion_count();
    const unsigned mana_cost = this->mana_cost(game);

    if(current_minion_count == Board::MAX_BOARD_SIZE || mana_cost > game.current_player().hero.mana)
        return {};


    for(unsigned board_position = 0; board_position <= current_minion_count; ++board_position)
        for(unsigned target_position = 0; target_position <= current_minion_count; ++target_position)
        {
            if(target_position == board_position)
                continue;
            play_self_actions.push_back(std::make_unique<PlayMinionAction>(
                hand_position, mana_cost, board_position, std::vector<OnPlayArg>{board_position, target_position}
            ));
        }

    return play_self_actions;
}