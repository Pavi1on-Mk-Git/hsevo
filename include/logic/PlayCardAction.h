#ifndef PLAY_CARD_ACTION_H
#define PLAY_CARD_ACTION_H

#include <variant>
#include <vector>

#include "logic/Action.h"
#include "logic/TargetType.h"

using OnPlayArg = std::variant<unsigned, TargetType>;

struct PlayCardAction: Action
{
    const unsigned hand_position, board_position, card_cost;
    std::vector<OnPlayArg> args;

    PlayCardAction(
        unsigned hand_position, unsigned board_position, unsigned card_cost, const std::vector<OnPlayArg>& args = {}
    );
    void apply(Game& game);
};

#endif