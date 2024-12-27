#include "logic/HeroPowerAction.h"

#include <spdlog/spdlog.h>

#include "logic/Game.h"

std::vector<Game> HeroPowerAction::apply(const Game& game) const
{
    SPDLOG_INFO("Player has used their hero power");
    return game.do_action(*this);
}

std::vector<Game> HeroPowerAction::test_apply(const Game& game) const
{
    return game.do_action(*this);
}

std::deque<GuiElementId> HeroPowerAction::element_sequence() const
{
    return {std::make_pair(GuiElementIdType::HERO_POWER, true)};
}