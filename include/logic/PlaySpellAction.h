#ifndef PLAY_SPELL_ACTION_H
#define PLAY_SPELL_ACTION_H


#include "logic/PlayCardAction.h"

/**
 * Action of playing a non-minion card from hand
 */
struct PlaySpellAction: public PlayCardAction
{
    /**
     * Construct an action
     * @param hand_position Position of the card in hand
     * @param card_cost Cost of the card at the moment of playing it
     * @param args Arguments with which the card has been played
     */
    PlaySpellAction(unsigned hand_position, unsigned card_cost, const std::vector<OnPlayArg>& args = {});
    std::vector<Game> apply(const Game& game) const override;
    std::vector<Game> test_apply(const Game& game) const override;
    std::deque<GuiElementId> element_sequence() const override;
};

#endif