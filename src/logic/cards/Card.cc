#include "logic/cards/Card.h"

#include "logic/Game.h"

Card::Card(std::string_view name, unsigned base_cost): mana_cost_(base_cost), name(name) {}

unsigned Card::mana_cost(const Game& game) const
{
    static_cast<void>(game);

    return mana_cost_;
}

std::vector<Game> Card::on_play(Game& game, const std::vector<OnPlayArg>& args)
{
    static_cast<void>(args);
    return {game};
}

std::vector<std::unique_ptr<PlayCardAction>> Card::create_play_actions(const Game& game, unsigned hand_position)
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    play_self_actions.push_back(std::make_unique<PlaySpellAction>(hand_position, this->mana_cost(game)));

    return play_self_actions;
}