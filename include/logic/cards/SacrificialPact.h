#ifndef SACRIFICIAL_PACT_H
#define SACRIFICIAL_PACT_H

#include "logic/cards/Card.h"

class SacrificialPact: public Card
{
private:
    SacrificialPact(): Card("Sacrificial Pact", 0) {}
public:
    static const SacrificialPact instance;
    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;
    std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position)
        const override;
};

inline const SacrificialPact SacrificialPact::instance;

#endif