#include "logic/cards/EarthenRingFarseer.h"

#include "logic/Game.h"

const unsigned EARTHEN_RING_FARSEER_HEAL_AMOUNT = 3;

std::vector<Game> EarthenRingFarseer::on_play(Game& game, const std::vector<OnPlayArg>& args)
{
    apply_to_entity(game, args, [](Entity& entity) { entity.restore_health(EARTHEN_RING_FARSEER_HEAL_AMOUNT); });
    return {game};
}

std::vector<std::unique_ptr<PlayCardAction>> EarthenRingFarseer::create_play_actions(
    const Game& game, unsigned hand_position
)
{
    using enum TargetType;

    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned current_minion_count = game.current_player().board.minion_count();
    const unsigned mana_cost = this->mana_cost(game);

    if(current_minion_count == Board::MAX_BOARD_SIZE || mana_cost > game.current_player().mana)
        return {};


    for(unsigned board_position = 0; board_position <= current_minion_count; ++board_position)
    {
        play_self_actions.push_back(std::make_unique<PlayMinionAction>(
            hand_position, mana_cost, board_position, std::vector<OnPlayArg>{ALLY_HERO}
        ));

        for(unsigned target_position = 0; target_position <= current_minion_count; ++target_position)
        {
            if(target_position == board_position)
                continue;
            play_self_actions.push_back(std::make_unique<PlayMinionAction>(
                hand_position, mana_cost, board_position, std::vector<OnPlayArg>{ALLY_MINION, target_position}
            ));
        }

        play_self_actions.push_back(std::make_unique<PlayMinionAction>(
            hand_position, mana_cost, board_position, std::vector<OnPlayArg>{ENEMY_HERO}
        ));

        for(unsigned target_position = 0; target_position < game.opponent().board.minion_count(); ++target_position)
            play_self_actions.push_back(std::make_unique<PlayMinionAction>(
                hand_position, mana_cost, board_position, std::vector<OnPlayArg>{ENEMY_MINION, target_position}
            ));
    }

    return play_self_actions;
}