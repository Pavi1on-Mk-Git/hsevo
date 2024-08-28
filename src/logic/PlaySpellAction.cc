#include "logic/PlaySpellAction.h"

#include "logic/Game.h"

PlaySpellAction::PlaySpellAction(unsigned hand_position, unsigned card_cost, const std::vector<OnPlayArg>& args):
    PlayCardAction(hand_position, card_cost, args)
{}

void PlaySpellAction::apply(Game& game)
{
    game.do_action(*this);
}