#ifndef END_TURN_ACTION_H
#define END_TURN_ACTION_H

#include "Action.h"

struct EndTurnAction: Action
{
    void apply(Game& game);
};

#endif