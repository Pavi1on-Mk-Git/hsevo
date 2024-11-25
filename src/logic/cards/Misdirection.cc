#include "logic/cards/Misdirection.h"

#include "logic/Game.h"

std::vector<Game> Misdirection::on_play(const Game& prev_state, const std::vector<OnPlayArg>&) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    game.current_player().secrets.push_back(this);
    return resulting_states;
}

std::optional<SecretResult> Misdirection::on_trigger(const Game& prev_state, const FightAction& action) const
{
    using enum TargetType;

    std::vector<FightAction> actions;

    switch(action.attacker)
    {
    case ALLY_MINION:
        switch(action.defender)
        {
        case ENEMY_HERO:
            for(unsigned minion_position = 0; minion_position < prev_state.current_player().board.minion_count();
                ++minion_position)
                if(minion_position != action.attacker_position)
                    actions.emplace_back(ALLY_MINION, *action.attacker_position, ALLY_MINION, minion_position);

            for(unsigned minion_position = 0; minion_position < prev_state.opponent().board.minion_count();
                ++minion_position)
                actions.emplace_back(ALLY_MINION, *action.attacker_position, ENEMY_MINION, minion_position);

            actions.emplace_back(ALLY_MINION, *action.attacker_position, ALLY_HERO);
            break;
        default:
            break;
        }
        break;
    case ALLY_HERO:
        switch(action.defender)
        {
        case ENEMY_HERO:
            for(unsigned minion_position = 0; minion_position < prev_state.current_player().board.minion_count();
                ++minion_position)
                actions.emplace_back(ALLY_HERO, ALLY_MINION, minion_position);

            for(unsigned minion_position = 0; minion_position < prev_state.opponent().board.minion_count();
                ++minion_position)
                actions.emplace_back(ALLY_HERO, ENEMY_MINION, minion_position);
            break;
        default:
            break;
        }
        break;
    default:
        return std::nullopt;
        ;
    }

    if(actions.empty())
        return std::nullopt;

    std::vector<Game> states;
    for(unsigned i = 0; i < actions.size(); ++i)
        states.push_back(prev_state);

    return SecretResult(states, actions, true);
}

std::vector<std::unique_ptr<PlayCardAction>> Misdirection::create_play_actions(const Game& game, unsigned hand_position)
    const
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned mana_cost = this->mana_cost(game);

    if(game.current_player().mana < mana_cost)
        return {};

    if(std::ranges::find(game.current_player().secrets, this) == game.current_player().secrets.end())
        play_self_actions.push_back(std::make_unique<PlaySpellAction>(hand_position, mana_cost));

    return play_self_actions;
}
