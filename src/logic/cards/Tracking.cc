#include "logic/cards/Tracking.h"

#include "logic/Game.h"

unsigned Tracking::amount_to_choose_from(const Game& game)
{
    return std::min(CHOICES, game.current_player().deck.size());
}

std::vector<Game> Tracking::on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    auto top_cards = game.current_player().deck.draw(amount_to_choose_from(game));

    if(!top_cards.first.empty())
    {
        const auto chosen_card = std::get<unsigned>(args.at(0));

        game.current_player().hand.add_cards(top_cards.first.at(chosen_card));
    }

    return resulting_states;
}

std::vector<std::unique_ptr<PlayCardAction>> Tracking::create_play_actions(const Game& game, unsigned hand_position)
    const
{
    std::vector<std::unique_ptr<PlayCardAction>> play_self_actions;

    const unsigned mana_cost = this->mana_cost(game);

    if(mana_cost > game.current_player().mana)
        return {};

    const unsigned card_choices = amount_to_choose_from(game);

    if(card_choices == 0)
        play_self_actions.push_back(std::make_unique<PlaySpellAction>(hand_position, mana_cost));
    else
        for(unsigned chosen_card = 0; chosen_card < card_choices; ++chosen_card)
            play_self_actions.push_back(
                std::make_unique<PlaySpellAction>(hand_position, mana_cost, std::vector<OnPlayArg>{chosen_card})
            );

    return play_self_actions;
}