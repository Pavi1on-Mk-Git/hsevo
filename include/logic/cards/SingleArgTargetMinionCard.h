#ifndef SINGLE_ARG_TARGET_MINION_CARD_H
#define SINGLE_ARG_TARGET_MINION_CARD_H

#include "logic/cards/Card.h"

class SingleArgTargetMinionCard: public Card
{
protected:
    using Card::Card;
public:
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position)
        const override;
};

#endif