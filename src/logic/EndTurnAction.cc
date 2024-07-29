#include "logic/EndTurnAction.h"

#include "logic/Game.h"

void EndTurnAction::apply(Game& game)
{
    game.do_action(*this);
}