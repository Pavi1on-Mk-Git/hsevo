#ifndef LEPER_GNOME_H
#define LEPER_GNOME_H

#include "logic/cards/MinionCard.h"

class LeperGnome: public MinionCard
{
private:
    LeperGnome(): MinionCard("Leper Gnome", 1, 2, 1, true) {}
public:
    static const LeperGnome instance;
    std::vector<Game> on_death(Game& game, unsigned id, unsigned player_id) const override;
};

inline const LeperGnome LeperGnome::instance;

#endif