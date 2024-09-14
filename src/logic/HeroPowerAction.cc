#include "logic/HeroPowerAction.h"

#include "logic/Game.h"

HeroPowerAction::HeroPowerAction(const std::vector<OnPlayArg>& args): args(args) {}

std::vector<Game> HeroPowerAction::apply(Game& game) const
{
    return game.do_action(*this);
}