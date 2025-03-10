#include "logic/PlaySpellAction.h"

#include <spdlog/spdlog.h>

#include "logic/Game.h"

PlaySpellAction::PlaySpellAction(unsigned hand_position, unsigned card_cost, const std::vector<OnPlayArg>& args):
    PlayCardAction(hand_position, card_cost, args)
{}

std::vector<Game> PlaySpellAction::apply(const Game& game) const
{
    SPDLOG_INFO(
        "Player has played {} from hand position {} for {} mana{}",
        game.current_player().hand.get_card(hand_position).card->name, hand_position, card_cost, args
    );
    return game.do_action(*this);
}

std::vector<Game> PlaySpellAction::test_apply(const Game& game) const
{
    return game.do_action(*this);
}

std::deque<GuiElementId> PlaySpellAction::element_sequence() const
{
    using enum GuiElementIdType;
    std::deque<GuiElementId> sequence;
    sequence.push_back(std::make_tuple(CARD, true, hand_position));
    auto args_sequence = get_element_sequence(args);
    std::ranges::move(args_sequence, std::back_inserter(sequence));
    return sequence;
}
