#include "logic/HitHeroAction.h"

#include "logic/Game.h"

HitHeroAction::HitHeroAction(unsigned position): position(position) {}

std::vector<Game> HitHeroAction::apply(Game& game) const
{
    return game.do_action(*this);
}

std::deque<GuiElementId> HitHeroAction::element_sequence() const
{
    using enum GuiElementIdType;
    std::deque<GuiElementId> sequence;
    sequence.push_back(std::make_tuple(MINION, true, position));
    sequence.push_back(std::make_pair(HERO, false));
    return sequence;
}