#include "logic/cards/Card.h"

#include "logic/Game.h"

Card::Card(const char* name, unsigned base_cost): mana_cost_(base_cost), name(name) {}

unsigned Card::mana_cost(const Game&) const
{
    return mana_cost_;
}

std::vector<Game> Card::on_play(const Game& prev_state, const std::vector<OnPlayArg>&) const
{
    return {prev_state};
}

std::vector<std::unique_ptr<PlayCardAction>> Card::create_play_actions(const Game& game, unsigned hand_position) const
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned mana_cost = this->mana_cost(game);

    if(game.current_player().mana >= mana_cost)
        play_self_actions.push_back(std::make_unique<PlaySpellAction>(hand_position, mana_cost));

    return play_self_actions;
}