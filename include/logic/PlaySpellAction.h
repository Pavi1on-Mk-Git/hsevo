#ifndef PLAY_SPELL_ACTION_H
#define PLAY_SPELL_ACTION_H


#include "logic/PlayCardAction.h"

struct PlaySpellAction: public PlayCardAction
{
    PlaySpellAction(unsigned hand_position, unsigned card_cost, const std::vector<OnPlayArg>& args = {});
    void apply(Game& game);
};

#endif