#include "TradeAction.h"

#include "Game.h"

TradeAction::TradeAction(unsigned int first_target, unsigned int second_target):
    first_target(first_target), second_target(second_target)
{}

void TradeAction::apply(Game& game)
{
    game.do_action(*this);
}