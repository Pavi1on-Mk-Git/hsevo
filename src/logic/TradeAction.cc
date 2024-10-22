#include "logic/TradeAction.h"

#include "logic/Game.h"

TradeAction::TradeAction(unsigned first_target, unsigned second_target):
    first_target(first_target), second_target(second_target)
{}

std::vector<Game> TradeAction::apply(Game& game) const
{
    return game.do_action(*this);
}

std::deque<GuiElementId> TradeAction::element_sequence() const
{
    using enum GuiElementIdType;
    std::deque<GuiElementId> sequence;
    sequence.push_back(std::make_tuple(MINION, true, first_target));
    sequence.push_back(std::make_tuple(MINION, false, second_target));
    return sequence;
}
