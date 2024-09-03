#include "logic/cards/PowerOverwhelming.h"

#include "logic/Game.h"

std::vector<Game> PowerOverwhelming::on_play(Game& game, const std::vector<OnPlayArg>& args)
{
    auto target_position = std::get<unsigned>(args.at(0));

    auto& minion = game.current_player().hero.board.get_minion(target_position);
    minion.attack += 4;
    minion.max_health += 4;
    minion.health += 4;
    minion.will_die_horribly = true;

    return {game};
}

std::vector<std::unique_ptr<PlayCardAction>> PowerOverwhelming::create_play_actions(
    const Game& game, unsigned hand_position
)
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned mana_cost = this->mana_cost(game);

    if(mana_cost > game.current_player().hero.mana)
        return {};

    for(unsigned target_position = 0; target_position <= game.current_player().hero.board.minion_count();
        ++target_position)
        play_self_actions.push_back(
            std::make_unique<PlaySpellAction>(hand_position, mana_cost, std::vector<OnPlayArg>{target_position})
        );

    return play_self_actions;
}