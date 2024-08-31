#ifndef ACTION_H
#define ACTION_H

#include <vector>

struct Game;

struct Action
{
    virtual ~Action() = default;
    virtual std::vector<Game> apply(Game& game) const = 0;
};

#endif