#ifndef RANDOM_PLAYER_LOGIC_H
#define RANDOM_PLAYER_LOGIC_H


#include "logic/Action.h"
#include "players/PlayerLogic.h"
#include "utils/Rng.h"

/**
 * Logic of a player who makes decisions completely randomly
 */
class RandomPlayerLogic: PlayerLogic
{
private:
    /**
     * Source of randomness
     */
    Rng& rng_;
public:
    /**
     * Construct a player logic
     * @param decklist Decklist used by the player
     * @param rng Source of randomness
     */
    RandomPlayerLogic(const Decklist& decklist, Rng& rng);
    Game choose_and_apply_action(const Game& game, const std::vector<std::unique_ptr<Action>>& actions) const override;
};

#endif