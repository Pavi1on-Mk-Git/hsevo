#ifndef PLAY_SPELL_ACTION_H
#define PLAY_SPELL_ACTION_H


#include "logic/PlayCardAction.h"

struct PlaySpellAction: public PlayCardAction
{
    PlaySpellAction(unsigned hand_position, unsigned card_cost, const std::vector<OnPlayArg>& args = {});
    std::vector<Game> apply(const Game& game) const override;
    std::vector<Game> test_apply(const Game& game) const override;
    std::deque<GuiElementId> element_sequence() const override;
};

#endif