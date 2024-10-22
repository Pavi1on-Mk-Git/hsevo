#include "logic/PlayMinionAction.h"

#include "logic/Game.h"

PlayMinionAction::PlayMinionAction(
    unsigned hand_position, unsigned card_cost, unsigned board_position, const std::vector<OnPlayArg>& args
): PlayCardAction(hand_position, card_cost, args), board_position(board_position)
{}

std::vector<Game> PlayMinionAction::apply(Game& game) const
{
    return game.do_action(*this);
}

std::deque<GuiElementId> PlayMinionAction::element_sequence() const
{
    using enum GuiElementIdType;
    std::deque<GuiElementId> sequence;
    sequence.push_back(std::make_pair(CARD, hand_position));
    sequence.push_back(std::make_pair(MINION, board_position));
    auto args_sequence = get_element_sequence(args);
    std::ranges::move(args_sequence, std::back_inserter(sequence));
    return sequence;
}
