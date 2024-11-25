#ifndef ACTION_H
#define ACTION_H

#include <deque>
#include <vector>

#include "utils/GuiElementId.h"

struct Game;

struct Action
{
    virtual ~Action() = default;
    virtual std::vector<Game> apply(const Game& game) const = 0;
    virtual std::vector<Game> test_apply(const Game& game) const = 0;
    virtual std::deque<GuiElementId> element_sequence() const = 0;
};

#endif