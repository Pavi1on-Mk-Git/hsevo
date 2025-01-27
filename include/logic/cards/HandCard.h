#ifndef HAND_CARD_H
#define HAND_CARD_H

#include "logic/cards/Card.h"

/**
 * Represents a card with possible modifiers it may receive while in player's hand
 */
struct HandCard
{
    /**
     * Amount by which the card's cost is increased
     */
    unsigned mana_cost_increase;

    /**
     * Underlying card
     */
    const Card* card;

    /**
     * Create a HandCard
     * @param card Underlying card
     * @param mana_cost_increase Card's cost increase
     */
    HandCard(const Card* card, unsigned mana_cost_increase = 0);

    /**
     * Calls `mana_cost` of the underlying card
     * @param game Game state
     * @return Cost of the card
     */
    unsigned mana_cost(const Game& game) const;

    /**
     * Calls `on_play` of the underlying card
     * @param prev_state Previous game state
     * @param args Additional arguments with which the card has been played
     * @return Resulting game states
     */
    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const;

    /**
     * Calls `create_play_actions` of the underlying card
     * @param game Current game state
     * @param hand_position Card's position in hand
     * @return Actions representing the act of playing the card in provided game state
     */
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position) const;
};

#endif