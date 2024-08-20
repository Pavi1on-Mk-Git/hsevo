#ifndef SINGLE_ARG_SELF_PLAY_POSITION_CARD_H
#define SINGLE_ARG_SELF_PLAY_POSITION_CARD_H

#include "logic/cards/Card.h"

struct SingleArgSelfPlayPositionCard: public Card
{
protected:
    using Card::Card;
public:
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position) override;
};

#endif