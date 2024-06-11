#include "PlayCardAction.h"

#include "Game.h"

void PlayCardAction::apply(Game& game)
{
    game.do_action(*this);
}