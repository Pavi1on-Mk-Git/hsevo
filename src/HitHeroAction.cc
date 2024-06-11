#include "HitHeroAction.h"

#include "Game.h"

HitHeroAction::HitHeroAction(unsigned int position): position(position) {}

void HitHeroAction::apply(Game& game)
{
    game.do_action(*this);
}