#ifndef EARTHEN_RING_FARSEER_H
#define EARTHEN_RING_FARSEER_H

#include "logic/cards/Card.h"

struct EarthenRingFarseer: public Card
{
    EarthenRingFarseer(): Card("Earthen Ring Farseer", 3, 3, 3) {}

    CLONE

    void on_play(Game& game, std::vector<OnPlayArg> args) override;
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position) override;
};

#endif