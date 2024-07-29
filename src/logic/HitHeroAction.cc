#include "logic/HitHeroAction.h"

#include "logic/Game.h"

HitHeroAction::HitHeroAction(unsigned position): position(position) {}

void HitHeroAction::apply(Game& game)
{
    game.do_action(*this);
}