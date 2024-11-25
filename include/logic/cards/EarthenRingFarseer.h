#ifndef EARTHEN_RING_FARSEER_H
#define EARTHEN_RING_FARSEER_H

#include "logic/cards/MinionCard.h"

class EarthenRingFarseer: public MinionCard
{
private:
    EarthenRingFarseer(): MinionCard("Earthen Ring Farseer", 3, 3, 3) {}
public:
    static const EarthenRingFarseer instance;
    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position)
        const override;
};

inline const EarthenRingFarseer EarthenRingFarseer::instance;

#endif