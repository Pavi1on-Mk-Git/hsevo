#include "logic/HeroTradeAction.h"

#include "logic/Game.h"

HeroTradeAction::HeroTradeAction(unsigned position): position(position) {}

std::vector<Game> HeroTradeAction::apply(Game& game) const
{
    return game.do_action(*this);
}

std::deque<GuiElementId> HeroTradeAction::element_sequence() const
{
    using enum GuiElementIdType;
    std::deque<GuiElementId> sequence;
    sequence.push_back(std::make_pair(HERO, true));
    sequence.push_back(std::make_tuple(MINION, false, position));
    return sequence;
}