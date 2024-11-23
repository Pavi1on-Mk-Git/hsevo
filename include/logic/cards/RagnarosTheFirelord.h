#ifndef RAGNAROS_THE_FIRELORD_H
#define RAGNAROS_THE_FIRELORD_H

#include "logic/cards/MinionCard.h"

class RagnarosTheFirelord: public MinionCard
{
private:
    RagnarosTheFirelord(): MinionCard("Ragnaros The Firelord", 8, 8, 8, CANT_ATTACK) {}
public:
    static const RagnarosTheFirelord instance;
    std::vector<Game> on_end_of_turn(Game& game, unsigned id) const override;
};

inline const RagnarosTheFirelord RagnarosTheFirelord::instance;

#endif