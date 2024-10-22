#include "logic/HeroHitHeroAction.h"

#include "logic/Game.h"

HeroHitHeroAction::HeroHitHeroAction() {}

std::vector<Game> HeroHitHeroAction::apply(Game& game) const
{
    return game.do_action(*this);
}

std::deque<GuiElementId> HeroHitHeroAction::element_sequence() const
{
    using enum GuiElementIdType;
    std::deque<GuiElementId> sequence;
    sequence.push_back(std::make_pair(HERO, true));
    sequence.push_back(std::make_pair(HERO, false));

    return sequence;
}