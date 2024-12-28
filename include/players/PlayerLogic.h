#ifndef PLAYER_LOGIC_H
#define PLAYER_LOGIC_H

#include <memory>

#include "logic/Action.h"
#include "logic/Decklist.h"

/**
 * Base class for all internal logics of players used in the game
 */
class PlayerLogic
{
protected:
    /**
     * Construct a player logic
     * @param decklist Decklist used by the player
     */
    PlayerLogic(const Decklist& decklist): decklist(decklist) {}
public:
    /**
     * Decklist used by the player
     */
    const Decklist& decklist;

    virtual ~PlayerLogic() = default;

    /**
     * Choose one action from the provided vector of actions and apply it to the game
     * @param game Current game state
     * @param actions Possible actions
     * @return Game state resulting from the chosen action
     */
    virtual Game choose_and_apply_action(const Game& game, const std::vector<std::unique_ptr<Action>>& actions)
        const = 0;
};


#endif