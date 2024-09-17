#include "logic/HeroTradeAction.h"

#include "logic/Game.h"

HeroTradeAction::HeroTradeAction(unsigned position): position(position) {}

std::vector<Game> HeroTradeAction::apply(Game& game) const
{
    return game.do_action(*this);
}