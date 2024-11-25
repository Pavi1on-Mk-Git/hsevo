#include "logic/cards/SacrificialPact.h"

#include <ranges>

#include "logic/Game.h"

std::vector<Game> SacrificialPact::on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    apply_to_entity(game, args, [](Entity& entity) { entity.health = 0; });
    return resulting_states;
}

std::vector<std::unique_ptr<PlayCardAction>> SacrificialPact::create_play_actions(
    const Game& game, unsigned hand_position
) const
{
    using enum Tribe;
    using enum TargetType;

    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned mana_cost = this->mana_cost(game);

    if(mana_cost > game.current_player().mana)
        return {};

    if(game.current_player().hero->tribe == DEMON)
        play_self_actions.push_back(
            std::make_unique<PlaySpellAction>(hand_position, mana_cost, std::vector<OnPlayArg>{ALLY_HERO})
        );

    for(auto [target_position, target_minion]: std::views::enumerate(game.current_player().board))
        if(target_minion.tribe == DEMON)
            play_self_actions.push_back(std::make_unique<PlaySpellAction>(
                hand_position, mana_cost, std::vector<OnPlayArg>{ALLY_MINION, static_cast<unsigned>(target_position)}
            ));

    if(game.opponent().hero->tribe == DEMON)
        play_self_actions.push_back(
            std::make_unique<PlaySpellAction>(hand_position, mana_cost, std::vector<OnPlayArg>{ENEMY_HERO})
        );

    for(auto [target_position, target_minion]: std::views::enumerate(game.opponent().board))
        if(target_minion.tribe == DEMON)
            play_self_actions.push_back(std::make_unique<PlaySpellAction>(
                hand_position, mana_cost, std::vector<OnPlayArg>{ENEMY_MINION, static_cast<unsigned>(target_position)}
            ));

    return play_self_actions;
}