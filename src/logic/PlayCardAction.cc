#include "logic/PlayCardAction.h"

#include "logic/Game.h"

PlayCardAction::PlayCardAction(
    unsigned hand_position, unsigned board_position, unsigned card_cost, const std::vector<OnPlayArg>& args
):
    hand_position(hand_position),
    board_position(board_position), card_cost(card_cost), args(args)
{}

void PlayCardAction::apply(Game& game)
{
    game.do_action(*this);
}