#include "logic/HeroHitHeroAction.h"

#include "logic/Game.h"

HeroHitHeroAction::HeroHitHeroAction() {}

std::vector<Game> HeroHitHeroAction::apply(Game& game) const
{
    return game.do_action(*this);
}