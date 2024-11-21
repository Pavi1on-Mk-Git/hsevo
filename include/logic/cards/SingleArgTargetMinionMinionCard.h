#ifndef SINGLE_ARG_TARGET_MINION_MINION_CARD
#define SINGLE_ARG_TARGET_MINION_MINION_CARD

#include "logic/cards/MinionCard.h"

class SingleArgTargetMinionMinionCard: public MinionCard
{
protected:
    using MinionCard::MinionCard;
public:
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position)
        const override;
};

#endif