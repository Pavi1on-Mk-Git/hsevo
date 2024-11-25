#include "logic/PlayMinionAction.h"

#include <spdlog/spdlog.h>

#include "logic/Game.h"

PlayMinionAction::PlayMinionAction(
    unsigned hand_position, unsigned card_cost, unsigned board_position, const std::vector<OnPlayArg>& args
): PlayCardAction(hand_position, card_cost, args), board_position(board_position)
{}

std::vector<Game> PlayMinionAction::apply(const Game& game) const
{
    SPDLOG_INFO(
        "Player has played {} from hand position {} for {} mana in board position {}{}",
        game.current_player().hand.get_card(hand_position).card->name, hand_position, card_cost, board_position, args
    );
    return game.do_action(*this);
}

std::vector<Game> PlayMinionAction::test_apply(const Game& game) const
{
    return game.do_action(*this);
}

std::deque<GuiElementId> PlayMinionAction::element_sequence() const
{
    using enum GuiElementIdType;
    std::deque<GuiElementId> sequence;
    sequence.push_back(std::make_tuple(CARD, true, hand_position));
    sequence.push_back(std::make_tuple(MINION, true, board_position));
    auto args_sequence = get_element_sequence(args);
    std::ranges::move(args_sequence, std::back_inserter(sequence));
    return sequence;
}
