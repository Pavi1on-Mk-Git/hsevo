#include "logic/PlaySpellAction.h"

#include "logic/Game.h"

PlaySpellAction::PlaySpellAction(unsigned hand_position, unsigned card_cost, const std::vector<OnPlayArg>& args):
    PlayCardAction(hand_position, card_cost, args)
{}

std::vector<Game> PlaySpellAction::apply(Game& game) const
{
    return game.do_action(*this);
}