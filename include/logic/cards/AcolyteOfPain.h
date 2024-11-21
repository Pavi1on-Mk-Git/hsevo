#ifndef ACOLYTE_OF_PAIN_H
#define ACOLYTE_OF_PAIN_H

#include "logic/cards/MinionCard.h"

class AcolyteOfPain: public MinionCard
{
private:
    AcolyteOfPain(): MinionCard("Acolyte of Pain", 3, 1, 3) {}
public:
    static const AcolyteOfPain instance;
    void on_damaged(Game& game, unsigned player_id) const override;
};

inline const AcolyteOfPain AcolyteOfPain::instance;

#endif