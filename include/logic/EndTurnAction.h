#ifndef END_TURN_ACTION_H
#define END_TURN_ACTION_H

#include "logic/Action.h"

struct EndTurnAction: Action
{
    void apply(Game& game);
};

#endif