#include "logic/HeroPowerAction.h"

#include <spdlog/spdlog.h>

#include "logic/Game.h"

HeroPowerAction::HeroPowerAction(const std::vector<OnPlayArg>& args): args(args) {}

std::vector<Game> HeroPowerAction::apply(Game& game) const
{
    SPDLOG_INFO("Player has used their hero power");
    return game.do_action(*this);
}

std::vector<Game> HeroPowerAction::test_apply(Game& game) const
{
    return game.do_action(*this);
}

std::deque<GuiElementId> HeroPowerAction::element_sequence() const
{
    std::deque<GuiElementId> sequence;
    sequence.emplace_back(std::make_pair(GuiElementIdType::HERO_POWER, true));
    auto args_sequence = get_element_sequence(args);
    std::ranges::move(args_sequence, std::back_inserter(sequence));
    return sequence;
}