#include "logic/cards/SacrificialPact.h"

#include "logic/Game.h"

std::vector<Game> SacrificialPact::on_play(Game& game, const std::vector<OnPlayArg>& args)
{
    return apply_to_entity(game, args, [](Entity& entity) { entity.health = 0; });
}

std::vector<std::unique_ptr<PlayCardAction>> SacrificialPact::create_play_actions(
    const Game& game, unsigned hand_position
)
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned mana_cost = this->mana_cost(game);

    if(mana_cost > game.current_player().hero.mana)
        return {};

    if(game.current_player().hero.tribe == Tribe::DEMON)
        play_self_actions.push_back(
            std::make_unique<PlaySpellAction>(hand_position, mana_cost, std::vector<OnPlayArg>{TargetType::ALLY_HERO})
        );

    for(unsigned target_position = 0; target_position <= game.current_player().hero.board.minion_count();
        ++target_position)
        if(game.current_player().hero.board.get_minion(target_position).tribe == Tribe::DEMON)
            play_self_actions.push_back(std::make_unique<PlaySpellAction>(
                hand_position, mana_cost, std::vector<OnPlayArg>{TargetType::ALLY_MINION, target_position}
            ));

    if(game.opponent().hero.tribe == Tribe::DEMON)
        play_self_actions.push_back(
            std::make_unique<PlaySpellAction>(hand_position, mana_cost, std::vector<OnPlayArg>{TargetType::ENEMY_HERO})
        );

    for(unsigned target_position = 0; target_position <= game.opponent().hero.board.minion_count(); ++target_position)
        if(game.opponent().hero.board.get_minion(target_position).tribe == Tribe::DEMON)
            play_self_actions.push_back(std::make_unique<PlaySpellAction>(
                hand_position, mana_cost, std::vector<OnPlayArg>{TargetType::ENEMY_MINION, target_position}
            ));

    return play_self_actions;
}