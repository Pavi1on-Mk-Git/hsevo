#ifndef GROMMASH_HELLSCREAM_H
#define GROMMASH_HELLSCREAM_H

#include "logic/cards/MinionCard.h"

class GrommashHellscream: public MinionCard
{
private:
    GrommashHellscream(): MinionCard("Grommash Hellscream", 8, 4, 9, CHARGE) {}
public:
    static const GrommashHellscream instance;
    void on_enrage(Minion& minion) const override;
    void on_no_enrage(Minion& minion) const override;
};

inline const GrommashHellscream GrommashHellscream::instance;

#endif