#ifndef STARVING_BUZZARD_H
#define STARVING_BUZZARD_H

#include "logic/cards/MinionCard.h"

class StarvingBuzzard: public MinionCard
{
private:
    StarvingBuzzard(): MinionCard("Starving Buzzard", 2, 2, 1, Tribe::BEAST) {}
public:
    static const StarvingBuzzard instance;
    void on_minion_summon(Game& game, Minion& minion, unsigned id) const override;
};

inline const StarvingBuzzard StarvingBuzzard::instance;

#endif