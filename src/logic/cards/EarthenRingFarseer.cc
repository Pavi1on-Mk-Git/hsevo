#include "logic/cards/EarthenRingFarseer.h"

#include "logic/Game.h"

const unsigned EARTHEN_RING_FARSEER_HEAL_AMOUNT = 3;

void EarthenRingFarseer::on_play(Game& game, std::vector<OnPlayArg> args)
{
    const auto target_type = std::get<TargetType>(args.at(0));

    switch(target_type)
    {
    case TargetType::ALLY_HERO:
        game.current_player().state.restore_health(EARTHEN_RING_FARSEER_HEAL_AMOUNT);
        return;
    case TargetType::ENEMY_HERO:
        game.opponent().state.restore_health(EARTHEN_RING_FARSEER_HEAL_AMOUNT);
        return;
    default:
        const auto target_position = std::get<unsigned>(args.at(1));
        if(target_type == TargetType::ALLY_MINION)
            game.current_player()
                .state.board.get_minion(target_position)
                .restore_health(EARTHEN_RING_FARSEER_HEAL_AMOUNT);
        else if(target_type == TargetType::ENEMY_MINION)
            game.opponent().state.board.get_minion(target_position).restore_health(EARTHEN_RING_FARSEER_HEAL_AMOUNT);
        return;
    }
}

std::vector<std::unique_ptr<PlayCardAction>> EarthenRingFarseer::create_play_actions(
    const Game& game, unsigned hand_position
)
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned current_minion_count = game.current_player().state.board.minion_count();
    const unsigned mana_cost = this->mana_cost(game);

    if(current_minion_count == Board::MAX_BOARD_SIZE || mana_cost > game.current_player().state.mana)
        return {};


    for(unsigned board_position = 0; board_position <= current_minion_count; ++board_position)
    {
        play_self_actions.push_back(std::make_unique<PlayMinionAction>(
            hand_position, mana_cost, board_position, std::vector<OnPlayArg>{TargetType::ALLY_HERO}
        ));

        for(unsigned target_position = 0; target_position <= current_minion_count; ++target_position)
        {
            if(target_position == board_position)
                continue;
            play_self_actions.push_back(std::make_unique<PlayMinionAction>(
                hand_position, mana_cost, board_position,
                std::vector<OnPlayArg>{TargetType::ALLY_MINION, target_position}
            ));
        }

        play_self_actions.push_back(std::make_unique<PlayMinionAction>(
            hand_position, mana_cost, board_position, std::vector<OnPlayArg>{TargetType::ENEMY_HERO}
        ));

        for(unsigned target_position = 0; target_position <= game.opponent().state.board.minion_count();
            ++target_position)
            play_self_actions.push_back(std::make_unique<PlayMinionAction>(
                hand_position, mana_cost, board_position,
                std::vector<OnPlayArg>{TargetType::ENEMY_MINION, target_position}
            ));
    }

    return play_self_actions;
}