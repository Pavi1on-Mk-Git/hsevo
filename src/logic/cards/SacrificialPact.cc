#include "logic/cards/SacrificialPact.h"

#include <ranges>

#include "logic/Game.h"

std::vector<Game> SacrificialPact::on_play(Game& game, const std::vector<OnPlayArg>& args) const
{
    apply_to_entity(game, args, [](Entity& entity) { entity.health = 0; });
    return {game};
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

    for(unsigned target_position = 0; target_position < game.current_player().board.minion_count(); ++target_position)
        if(game.current_player().board.get_minion(target_position).tribe == DEMON)
            play_self_actions.push_back(std::make_unique<PlaySpellAction>(
                hand_position, mana_cost, std::vector<OnPlayArg>{ALLY_MINION, target_position}
            ));

    if(game.opponent().hero->tribe == DEMON)
        play_self_actions.push_back(
            std::make_unique<PlaySpellAction>(hand_position, mana_cost, std::vector<OnPlayArg>{ENEMY_HERO})
        );

    for(unsigned target_position = 0; target_position < game.opponent().board.minion_count(); ++target_position)
        if(game.opponent().board.get_minion(target_position).tribe == DEMON)
            play_self_actions.push_back(std::make_unique<PlaySpellAction>(
                hand_position, mana_cost, std::vector<OnPlayArg>{ENEMY_MINION, target_position}
            ));

    return play_self_actions;
}