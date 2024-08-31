#include "logic/HitHeroAction.h"

#include "logic/Game.h"

HitHeroAction::HitHeroAction(unsigned position): position(position) {}

std::vector<Game> HitHeroAction::apply(Game& game) const
{
    return game.do_action(*this);
}