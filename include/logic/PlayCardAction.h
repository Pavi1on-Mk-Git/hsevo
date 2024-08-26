#ifndef PLAY_CARD_ACTION_H
#define PLAY_CARD_ACTION_H

#include <variant>
#include <vector>

#include "logic/Action.h"
#include "logic/TargetType.h"

using OnPlayArg = std::variant<unsigned, TargetType>;

class PlayCardAction: public Action
{
protected:
    PlayCardAction(unsigned hand_position, unsigned card_cost, const std::vector<OnPlayArg>& args = {});
public:
    const unsigned hand_position, card_cost;
    std::vector<OnPlayArg> args;

    virtual ~PlayCardAction() = default;
};


#endif