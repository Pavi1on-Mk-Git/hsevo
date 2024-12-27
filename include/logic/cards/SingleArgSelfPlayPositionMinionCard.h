#ifndef SINGLE_ARG_SELF_PLAY_POSITION_MINION_CARD_H
#define SINGLE_ARG_SELF_PLAY_POSITION_MINION_CARD_H

#include "logic/cards/MinionCard.h"

/**
 * Base class for all minion cards who need to know their position when played
 */
class SingleArgSelfPlayPositionMinionCard: public MinionCard
{
protected:
    using MinionCard::MinionCard;
public:
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position)
        const override;
};

#endif