#include "logic/EndTurnAction.h"

#include "logic/Game.h"

std::vector<Game> EndTurnAction::apply(Game& game) const
{
    return game.do_action(*this);
}

std::deque<GuiElementId> EndTurnAction::element_sequence() const
{
    return {GuiElementIdType::EOT_BUTTON};
}