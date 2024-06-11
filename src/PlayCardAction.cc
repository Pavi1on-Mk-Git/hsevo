#include "PlayCardAction.h"

#include "Game.h"

PlayCardAction::PlayCardAction(unsigned int hand_position, unsigned int board_position, unsigned int card_cost):
    hand_position(hand_position), board_position(board_position), card_cost(card_cost)
{}

void PlayCardAction::apply(Game& game)
{
    game.do_action(*this);
}