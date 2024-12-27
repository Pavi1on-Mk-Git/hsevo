#ifndef CARD_H
#define CARD_H

#include <memory>

#include "logic/PlayCardAction.h"

/**
 * Base class used to represent a card used in the game
 */
class Card
{
protected:
    /**
     * Base mana cost of the card
     */
    const unsigned mana_cost_;

    /**
     * Construct a card with provided name and cost
     * @param name Name of the card
     * @param base_cost Base cost of the card
     */
    Card(const char* name, unsigned base_cost);
public:
    /**
     * Name of the card
     */
    const char* name;

    virtual ~Card() = default;

    /**
     * Calculate the cost of the card in the current game state
     * @param game Game state
     * @return Cost of the card
     */
    virtual unsigned mana_cost(const Game& game) const;

    /**
     * Calculate all possible game states resulting from playing the card in the provided state
     * @param prev_state Previous game state
     * @param args Additional arguments with which the card has been played
     * @return Resulting game states
     */
    virtual std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const;

    /**
     * Create a vector of actions representing all possible ways the card can be played
     * @param game Current game state
     * @param hand_position Card's position in hand
     * @return Actions representing the act of playing the card in provided game state
     */
    virtual std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position)
        const;
};

#endif