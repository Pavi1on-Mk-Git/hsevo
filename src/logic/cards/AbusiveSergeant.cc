#include "logic/cards/AbusiveSergeant.h"

#include "logic/Entity.h"
#include "logic/Game.h"

const unsigned ABUSIVE_SERGEANT_BUFF_AMOUNT = 2;

std::vector<Game> AbusiveSergeant::on_play(Game& game, const std::vector<OnPlayArg>& args) const
{
    using enum TargetType;

    const auto target_type = std::get<TargetType>(args.at(0));
    const auto target_position = std::get<unsigned>(args.at(1));

    switch(target_type)
    {
    case ALLY_MINION:
        game.current_player().board.get_minion(target_position).attack += ABUSIVE_SERGEANT_BUFF_AMOUNT;
        break;
    case ENEMY_MINION:
        game.opponent().board.get_minion(target_position).attack += ABUSIVE_SERGEANT_BUFF_AMOUNT;
        break;
    default:
        break;
    }

    return {game};
}

std::vector<std::unique_ptr<PlayCardAction>> AbusiveSergeant::create_play_actions(
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
    {
        for(unsigned target_position = 0; target_position <= current_minion_count; ++target_position)
        {
            if(target_position == board_position)
                continue;
            play_self_actions.push_back(std::make_unique<PlayMinionAction>(
                hand_position, mana_cost, board_position, std::vector<OnPlayArg>{ALLY_MINION, target_position}
            ));
        }

        for(unsigned target_position = 0; target_position < game.opponent().board.minion_count(); ++target_position)
            play_self_actions.push_back(std::make_unique<PlayMinionAction>(
                hand_position, mana_cost, board_position, std::vector<OnPlayArg>{ENEMY_MINION, target_position}
            ));
    }

    return play_self_actions;
}