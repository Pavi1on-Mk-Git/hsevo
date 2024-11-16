#include "logic/cards/HandCard.h"

#include "logic/Game.h"

HandCard::HandCard(const Card* card, unsigned mana_cost_increase): mana_cost_increase_(mana_cost_increase), card(card)
{}

unsigned HandCard::mana_cost(Game& game) const
{
    return card->mana_cost(game) + mana_cost_increase_;
}

std::vector<Game> HandCard::on_play(Game& game, const std::vector<OnPlayArg>& args) const
{
    return card->on_play(game, args);
}

std::vector<std::unique_ptr<PlayCardAction>> HandCard::create_play_actions(const Game& game, unsigned hand_position)
    const
{
    return card->create_play_actions(game, hand_position);
}
