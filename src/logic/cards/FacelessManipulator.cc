#include "logic/cards/FacelessManipulator.h"

#include "logic/Game.h"

std::vector<Game> FacelessManipulator::on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    if(!args.empty())
    {
        const auto position_played = std::get<unsigned>(args.at(0));
        const auto target_position = std::get<unsigned>(args.at(2));

        auto& board = game.current_player().board;
        auto& faceless = board.get_minion(position_played);
        unsigned faceless_id = faceless.id;

        board.transform_minion(board.get_minion(target_position), position_played);

        faceless.active = faceless.keywords & MinionKeywords::CHARGE;
        faceless.id = faceless_id;
    }

    return resulting_states;
}

std::vector<std::unique_ptr<PlayCardAction>> FacelessManipulator::create_play_actions(
    const Game& game, unsigned hand_position
) const
{
    using enum TargetType;
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned current_minion_count = game.current_player().board.minion_count();
    const unsigned mana_cost = this->mana_cost(game);

    if(current_minion_count == Board::MAX_BOARD_SIZE || mana_cost > game.current_player().mana)
        return {};


    for(unsigned board_position = 0; board_position <= current_minion_count; ++board_position)
        for(unsigned target_position = 0; target_position <= current_minion_count; ++target_position)
        {
            if(target_position == board_position)
                continue;
            play_self_actions.push_back(std::make_unique<PlayMinionAction>(
                hand_position, mana_cost, board_position,
                std::vector<OnPlayArg>{board_position, ALLY_MINION, target_position}
            ));
        }

    if(play_self_actions.empty())
        for(unsigned board_position = 0; board_position <= current_minion_count; ++board_position)
            play_self_actions.push_back(std::make_unique<PlayMinionAction>(hand_position, mana_cost, board_position));

    return play_self_actions;
}