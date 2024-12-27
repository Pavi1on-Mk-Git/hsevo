#ifndef PLAY_MINION_ACTION_H
#define PLAY_MINION_ACTION_H


#include "logic/PlayCardAction.h"

/**
 * Action of playing a minion card from hand
 */
struct PlayMinionAction: public PlayCardAction
{
    /**
     * Position at which the minion will be played
     */
    const unsigned board_position;

    /**
     * Construct an action
     * @param hand_position Position of the card in hand
     * @param card_cost Cost of the card at the moment of playing it
     * @param board_position Position at which the minion will be played
     * @param args Arguments with which the card has been played
     */
    PlayMinionAction(
        unsigned hand_position, unsigned card_cost, unsigned board_position, const std::vector<OnPlayArg>& args = {}
    );
    std::vector<Game> apply(const Game& game) const override;
    std::vector<Game> test_apply(const Game& game) const override;
    std::deque<GuiElementId> element_sequence() const override;
};

#endif