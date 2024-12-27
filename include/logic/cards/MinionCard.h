#ifndef MINION_CARD_H
#define MINION_CARD_H

#include <memory>

#include "logic/MinionKeywords.h"
#include "logic/Tribe.h"
#include "logic/cards/Card.h"

struct Minion;

/**
 * Base class for all cards representing a minion
 */
class MinionCard: public Card
{
protected:
    /**
     * Construct a minion card
     * @param name Name of the card
     * @param base_cost Base cost of the card
     * @param base_attack Base attack of the card
     * @param base_health Base health of the card
     */
    MinionCard(const char* name, unsigned base_cost, unsigned base_attack, unsigned base_health);

    /**
     * Construct a minion card
     * @param name Name of the card
     * @param base_cost Base cost of the card
     * @param base_attack Base attack of the card
     * @param base_health Base health of the card
     * @param keywords Keywords of the minion represented by the card
     */
    MinionCard(
        const char* name, unsigned base_cost, unsigned base_attack, unsigned base_health, const MinionKeywords& keywords
    );

    /**
     * Construct a minion card
     * @param name Name of the card
     * @param base_cost Base cost of the card
     * @param base_attack Base attack of the card
     * @param base_health Base health of the card
     * @param tribe Tribe of the minion represented by the card
     */
    MinionCard(const char* name, unsigned base_cost, unsigned base_attack, unsigned base_health, const Tribe& tribe);

    /**
     * Construct a minion card
     * @param name Name of the card
     * @param base_cost Base cost of the card
     * @param base_attack Base attack of the card
     * @param base_health Base health of the card
     * @param has_deathrattle Flag signaling if the minion has a deathrattle effect
     */
    MinionCard(const char* name, unsigned base_cost, unsigned base_attack, unsigned base_health, bool has_deathrattle);

    /**
     * Construct a minion card
     * @param name Name of the card
     * @param base_cost Base cost of the card
     * @param base_attack Base attack of the card
     * @param base_health Base health of the card
     * @param keywords Keywords of the minion represented by the card
     * @param tribe Tribe of the minion represented by the card
     */
    MinionCard(
        const char* name, unsigned base_cost, unsigned base_attack, unsigned base_health,
        const MinionKeywords& keywords, const Tribe& tribe
    );

    /**
     * Construct a minion card
     * @param name Name of the card
     * @param base_cost Base cost of the card
     * @param base_attack Base attack of the card
     * @param base_health Base health of the card
     * @param keywords Keywords of the minion represented by the card
     * @param has_eot Flag signaling if the minion has an end-of-turn effect
     */
    MinionCard(
        const char* name, unsigned base_cost, unsigned base_attack, unsigned base_health,
        const MinionKeywords& keywords, bool has_eot
    );
public:
    /**
     * Base attack and health of the minion
     */
    const unsigned base_attack, base_health;

    /**
     * Keywords possesed by the minion
     */
    const MinionKeywords keywords;

    /**
     * Tribe to which the minion belongs
     */
    const Tribe tribe;

    /**
     * Flags signaling special qualities the minion may possess
     */
    bool has_deathrattle, has_eot;

    virtual ~MinionCard() = default;

    /**
     * Calculate all possible game states resulting from the minion dying in the provided state
     * @param prev_state Previous game state
     * @param player_id Id of the player to whom this minion belongs
     * @return Resulting game states
     */
    virtual std::vector<Game> on_death(const Game& prev_state, unsigned player_id) const;

    /**
     * Modify the game state when a minion has been summoned
     * @param game Current game state
     * @param minion Minion which has been summoned
     * @param id Id of this minion in the provided game state
     * @param player_id Id of the player to whom this minion belongs
     */
    virtual void on_minion_summon(Game& game, Minion& minion, unsigned id, unsigned player_id) const;

    /**
     * Modify the game state when a minion has been damaged
     * @param game Current game state
     * @param player_id Id of the player to whom this minion belongs
     */
    virtual void on_minion_damaged(Game& game, unsigned player_id) const;

    /**
     * Modify the game state when this minion has been damaged
     * @param game Current game state
     * @param player_id Id of the player to whom this minion belongs
     */
    virtual void on_damaged(Game& game, unsigned player_id) const;

    /**
     * Modify the game state when this minion is summoned
     * @param game Current game state
     * @param id Id of this minion in the provided game state
     */
    virtual void on_summon(Game& game, unsigned id) const;

    /**
     * Modify the game state when this minion is removed from the battlefield
     * @param game Current game state
     * @param id Id of this minion in the provided game state
     * @param player_id Id of the player to whom this minion belongs
     */
    virtual void on_remove(Game& game, unsigned id, unsigned player_id) const;

    /**
     * Calculate all possible game states resulting from this minion's end-of-turn effect
     * @param prev_state Previous game state
     * @param id Id of this minion in the provided game state
     * @return Resulting game states
     */
    virtual std::vector<Game> on_end_of_turn(const Game& prev_state, unsigned id) const;

    /**
     * Modify the provided minion when its health drops below its maximum value
     * @param minion Provided minion
     */
    virtual void on_enrage(Minion& minion) const;

    /**
     * Modify the provided minion when its health returns to its maximum value
     * @param minion Provided minion
     */
    virtual void on_calm_down(Minion& minion) const;

    virtual std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position)
        const override;
};

#endif
