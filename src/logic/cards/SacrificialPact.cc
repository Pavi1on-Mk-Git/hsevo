#include "logic/cards/SacrificialPact.h"

#include "logic/Game.h"

void SacrificialPact::on_play(Game& game, std::vector<OnPlayArg> args)
{
    const auto target_type = std::get<TargetType>(args.at(0));

    switch(target_type)
    {
    case TargetType::ALLY_HERO:
        game.current_player().state.health = 0;
        return;
    case TargetType::ENEMY_HERO:
        game.opponent().state.health = 0;
        return;
    default:
        const auto target_position = std::get<unsigned>(args.at(1));
        if(target_type == TargetType::ALLY_MINION)
            game.current_player().state.board.get_minion(target_position).health = 0;
        else if(target_type == TargetType::ENEMY_MINION)
            game.opponent().state.board.get_minion(target_position).health = 0;
        return;
    }
}

std::vector<std::unique_ptr<PlayCardAction>> SacrificialPact::create_play_actions(
    const Game& game, unsigned hand_position
)
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned mana_cost = this->mana_cost(game);

    if(mana_cost > game.current_player().state.mana)
        return {};

    if(game.current_player().state.tribe == Tribe::DEMON)
        play_self_actions.push_back(
            std::make_unique<PlaySpellAction>(hand_position, mana_cost, std::vector<OnPlayArg>{TargetType::ALLY_HERO})
        );

    for(unsigned target_position = 0; target_position <= game.current_player().state.board.minion_count();
        ++target_position)
        if(game.current_player().state.board.get_minion(target_position).tribe == Tribe::DEMON)
            play_self_actions.push_back(std::make_unique<PlaySpellAction>(
                hand_position, mana_cost, std::vector<OnPlayArg>{TargetType::ALLY_MINION, target_position}
            ));

    if(game.opponent().state.tribe == Tribe::DEMON)
        play_self_actions.push_back(
            std::make_unique<PlaySpellAction>(hand_position, mana_cost, std::vector<OnPlayArg>{TargetType::ENEMY_HERO})
        );

    for(unsigned target_position = 0; target_position <= game.opponent().state.board.minion_count(); ++target_position)
        if(game.opponent().state.board.get_minion(target_position).tribe == Tribe::DEMON)
            play_self_actions.push_back(std::make_unique<PlaySpellAction>(
                hand_position, mana_cost, std::vector<OnPlayArg>{TargetType::ENEMY_MINION, target_position}
            ));

    return play_self_actions;
}