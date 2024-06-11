#include "EndTurnAction.h"

#include "Game.h"

void EndTurnAction::apply(Game& game)
{
    game.do_action(*this);
}