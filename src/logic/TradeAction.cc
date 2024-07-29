#include "logic/TradeAction.h"

#include "logic/Game.h"

TradeAction::TradeAction(unsigned first_target, unsigned second_target):
    first_target(first_target), second_target(second_target)
{}

void TradeAction::apply(Game& game)
{
    game.do_action(*this);
}