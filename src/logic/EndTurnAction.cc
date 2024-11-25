#include "logic/EndTurnAction.h"

#include <spdlog/spdlog.h>

#include "logic/Game.h"

std::vector<Game> EndTurnAction::apply(const Game& game) const
{
    SPDLOG_INFO("Player has ended their turn");
    return game.do_action(*this);
}

std::vector<Game> EndTurnAction::test_apply(const Game& game) const
{
    return game.do_action(*this);
}

std::deque<GuiElementId> EndTurnAction::element_sequence() const
{
    return {GuiElementIdType::EOT_BUTTON};
}
