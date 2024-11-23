#ifndef BARON_GEDDON_H
#define BARON_GEDDON_H

#include "logic/cards/MinionCard.h"

class BaronGeddon: public MinionCard
{
private:
    BaronGeddon(): MinionCard("Baron Geddon", 7, 7, 5) {}
public:
    static const BaronGeddon instance;
    std::vector<Game> on_end_of_turn(Game& game, unsigned id, unsigned player_id) const override;
};

inline const BaronGeddon BaronGeddon::instance;

#endif