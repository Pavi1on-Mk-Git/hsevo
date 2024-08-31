#include "logic/PlayMinionAction.h"

#include "logic/Game.h"

PlayMinionAction::PlayMinionAction(
    unsigned hand_position, unsigned card_cost, unsigned board_position, const std::vector<OnPlayArg>& args
):
    PlayCardAction(hand_position, card_cost, args),
    board_position(board_position)
{}

std::vector<Game> PlayMinionAction::apply(Game& game) const
{
    return game.do_action(*this);
}