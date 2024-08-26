#ifndef SINGLE_ARG_SELF_PLAY_POSITION_CARD_H
#define SINGLE_ARG_SELF_PLAY_POSITION_CARD_H

#include "logic/cards/MinionCard.h"

struct SingleArgSelfPlayPositionCard: public MinionCard
{
protected:
    using MinionCard::MinionCard;
public:
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position) override;
};

#endif