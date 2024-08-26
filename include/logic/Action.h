#ifndef ACTION_H
#define ACTION_H

struct Game;

struct Action
{
    virtual ~Action() = default;
    virtual void apply(Game& game) = 0;
};

#endif