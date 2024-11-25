#include "logic/cards/Alexstraza.h"

#include "logic/Game.h"

const unsigned ALEXSTRAZA_HERO_HEALTH = 15;

std::vector<Game> Alexstraza::on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    apply_to_entity(game, args, [](Entity& entity) { entity.health = ALEXSTRAZA_HERO_HEALTH; });
    return resulting_states;
}

std::vector<std::unique_ptr<PlayCardAction>> Alexstraza::create_play_actions(const Game& game, unsigned hand_position)
    const
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

        play_self_actions.push_back(std::make_unique<PlayMinionAction>(
            hand_position, mana_cost, board_position, std::vector<OnPlayArg>{ENEMY_HERO}
        ));
    }

    return play_self_actions;
}
