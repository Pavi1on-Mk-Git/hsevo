#ifndef HAND_CARD_H
#define HAND_CARD_H

#include "logic/cards/Card.h"

class HandCard
{
private:
    unsigned mana_cost_increase_;
public:
    const Card* card;

    HandCard(const Card* card, unsigned mana_cost_increase = 0);
    unsigned mana_cost(Game& game) const;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const;
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position) const;
};

#endif