#ifndef PLAY_CARD_ACTION_H
#define PLAY_CARD_ACTION_H

#include <vector>

#include "logic/Action.h"
#include "logic/OnPlayArg.h"

/**
 * Base class for actions that involve playing a card from hand
 */
class PlayCardAction: public Action
{
protected:
    /**
     * Construct an action
     * @param hand_position Position of the card in hand
     * @param card_cost Cost of the card at the moment of playing it
     * @param args Arguments with which the card has been played
     */
    PlayCardAction(unsigned hand_position, unsigned card_cost, const std::vector<OnPlayArg>& args = {});
public:
    /**
     * Played card's position in hand and cost at the moment of playing it
     */
    const unsigned hand_position, card_cost;

    /**
     * Arguments with which the card has been played
     */
    const std::vector<OnPlayArg> args;

    virtual ~PlayCardAction() = default;
};


#endif