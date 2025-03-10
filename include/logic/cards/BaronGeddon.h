#ifndef BARON_GEDDON_H
#define BARON_GEDDON_H

#include "logic/cards/MinionCard.h"

class BaronGeddon: public MinionCard
{
private:
    BaronGeddon(): MinionCard("Baron Geddon", 7, 7, 5, NO_KEYWORDS, true) {}
public:
    static const BaronGeddon instance;
    std::vector<Game> on_end_of_turn(const Game& prev_state, unsigned id) const override;
};

inline const BaronGeddon BaronGeddon::instance;

#endif