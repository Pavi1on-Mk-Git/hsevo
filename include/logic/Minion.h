#ifndef MINION_H
#define MINION_H

#include "logic/Entity.h"
#include "logic/MinionKeywords.h"
#include "logic/cards/MinionCard.h"

/**
 * Represents a minion present on the board
 */
struct Minion: public Entity
{
    /**
     * Underlying minion card
     */
    const MinionCard* card;

    /**
     * Minion's attack and identifiers
     */
    unsigned attack, id, player_id;

    /**
     * Flags signaling the minion's status
     */
    bool active, will_die_horribly;

    /**
     * Gameplay keywords possessed by the minion
     */
    MinionKeywords keywords;

    /**
     * Ids of the minions whose auras are currently being applied to this minion
     */
    std::vector<unsigned> auras_applied;

    /**
     * Construct a minion from a card given the game state
     * @param card Underlying minion card
     * @param id Id of the minion
     * @param player_id Id of the player who owns this minion
     */
    Minion(const MinionCard* card, unsigned id, unsigned player_id);
    void restore_health(unsigned amount) override;
    void deal_dmg(unsigned amount, Game& game) override;

    /**
     * Calls `on_summon` of the underlying minion card
     * @param game Game state
     */
    void on_summon(Game& game) const;

    /**
     * Calls `on_remove` of the underlying minion card
     * @param game Game state
     */
    void on_remove(Game& game) const;

    /**
     * Calls `on_death` of the underlying minion card
     * @param prev_state Previous game state
     * @return Resulting game states
     */
    std::vector<Game> on_death(const Game& prev_state) const;

    /**
     * Calls `on_minion_summon` of the underlying minion card
     * @param game Game state
     * @param minion Summoned minion
     */
    void on_minion_summon(Game& game, Minion& minion) const;

    /**
     * Calls `on_minion_damaged` of the underlying minion card
     * @param game Game state
     */
    void on_minion_damaged(Game& game) const;

    /**
     * Calls `on_end_of_turn` of the underlying minion card
     * @param prev_state Previous game state
     * @return Resulting game states
     */
    std::vector<Game> on_end_of_turn(const Game& prev_state);
};


#endif