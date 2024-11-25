#include "logic/cards/BigGameHunter.h"

#include "logic/Game.h"

std::vector<Game> BigGameHunter::on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    if(!args.empty())
        apply_to_entity(game, args, [](Entity& entity) { entity.health = 0; });

    return resulting_states;
}

const unsigned BIG_GAME_HUNTER_ATTACK_THRESHOLD = 7;

std::vector<std::unique_ptr<PlayCardAction>> BigGameHunter::create_play_actions(
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

            if(game.current_player()
                   .board.get_minion(target_position < board_position ? target_position : target_position - 1)
                   .attack >= BIG_GAME_HUNTER_ATTACK_THRESHOLD)
                play_self_actions.push_back(std::make_unique<PlayMinionAction>(
                    hand_position, mana_cost, board_position, std::vector<OnPlayArg>{ALLY_MINION, target_position}
                ));
        }

        for(unsigned target_position = 0; target_position < game.opponent().board.minion_count(); ++target_position)
            if(game.opponent().board.get_minion(target_position).attack >= BIG_GAME_HUNTER_ATTACK_THRESHOLD)
                play_self_actions.push_back(std::make_unique<PlayMinionAction>(
                    hand_position, mana_cost, board_position, std::vector<OnPlayArg>{ENEMY_MINION, target_position}
                ));
    }

    if(play_self_actions.empty())
        for(unsigned board_position = 0; board_position <= current_minion_count; ++board_position)
            play_self_actions.push_back(std::make_unique<PlayMinionAction>(hand_position, mana_cost, board_position));

    return play_self_actions;
}