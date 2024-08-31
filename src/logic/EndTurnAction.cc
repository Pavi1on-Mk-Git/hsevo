#include "logic/EndTurnAction.h"

#include "logic/Game.h"

std::vector<Game> EndTurnAction::apply(Game& game) const
{
    return game.do_action(*this);
}