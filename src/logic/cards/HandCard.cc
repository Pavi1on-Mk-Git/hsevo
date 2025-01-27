#include "logic/cards/HandCard.h"

#include <algorithm>

#include "logic/Game.h"

HandCard::HandCard(const Card* card, unsigned mana_cost_increase): mana_cost_increase(mana_cost_increase), card(card) {}

unsigned HandCard::mana_cost(const Game& game) const
{
    return card->mana_cost(game) + mana_cost_increase;
}

std::vector<Game> HandCard::on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const
{
    return card->on_play(prev_state, args);
}

std::vector<std::unique_ptr<PlayCardAction>> HandCard::create_play_actions(const Game& game, unsigned hand_position)
    const
{
    auto actions = card->create_play_actions(game, hand_position);

    if(mana_cost_increase > 0)
        std::ranges::remove_if(actions, [&](const auto& action) {
            return action->card_cost + mana_cost_increase > game.current_player().mana;
        });

    return actions;
}
