#include "PlayCardAction.h"

#include "Game.h"

PlayCardAction::PlayCardAction(unsigned hand_position, unsigned board_position, unsigned card_cost):
    hand_position(hand_position), board_position(board_position), card_cost(card_cost)
{}

void PlayCardAction::apply(Game& game)
{
    game.do_action(*this);
}