#include "logic/cards/Execute.h"

#include "logic/Game.h"

std::vector<Game> Execute::on_play(Game& game, const std::vector<OnPlayArg>& args) const
{
    const auto target_position = std::get<unsigned>(args.at(1));

    game.opponent().board.get_minion(target_position).health = 0;
    return {game};
}

std::vector<std::unique_ptr<PlayCardAction>> Execute::create_play_actions(const Game& game, unsigned hand_position)
    const
{
    using enum TargetType;

    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned mana_cost = this->mana_cost(game);

    if(mana_cost > game.current_player().mana)
        return {};

    for(auto [target_position, target]: std::views::enumerate(game.opponent().board))
        if(target.max_health - target.health > 0)
            play_self_actions.push_back(std::make_unique<PlaySpellAction>(
                hand_position, mana_cost, std::vector<OnPlayArg>{ENEMY_MINION, static_cast<unsigned>(target_position)}
            ));

    return play_self_actions;
}