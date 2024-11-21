#ifndef ARMORSMITH_H
#define ARMORSMITH_H

#include "logic/cards/MinionCard.h"

class Armorsmith: public MinionCard
{
private:
    Armorsmith(): MinionCard("Armorsmith", 2, 1, 4) {}
public:
    static const Armorsmith instance;
    void on_minion_damaged(Game& game, unsigned player_id) const override;
};

inline const Armorsmith Armorsmith::instance;

#endif