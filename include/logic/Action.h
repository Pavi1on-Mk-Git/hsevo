#ifndef ACTION_H
#define ACTION_H

#include <deque>
#include <vector>

#include "utils/GuiElementId.h"

struct Game;

/**
 * Base class for all actions player may do in a game
 */
struct Action
{
    virtual ~Action() = default;

    /**
     * Compute all potential game states resulting from applying this action
     *
     * This function generates logs
     * @param game Game state
     * @return Resulting game states
     */
    virtual std::vector<Game> apply(const Game& game) const = 0;

    /**
     * Compute all potential game states resulting from applying this action
     *
     * This function doesn't disclose any information which the players shouldn't know and thus is supposed to be used
     * to test potential results of applying this action onto the game
     * @param game Game state
     * @return Resulting game states
     */
    virtual std::vector<Game> test_apply(const Game& game) const = 0;

    /**
     * Return a sequence of gui elements which clicked in that order would result in doing this action
     * @return Sequence of gui elements
     */
    virtual std::deque<GuiElementId> element_sequence() const = 0;
};

#endif