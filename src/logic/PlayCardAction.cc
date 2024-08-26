#include "logic/PlayCardAction.h"

PlayCardAction::PlayCardAction(unsigned hand_position, unsigned card_cost, const std::vector<OnPlayArg>& args):
    hand_position(hand_position), card_cost(card_cost), args(args)
{}