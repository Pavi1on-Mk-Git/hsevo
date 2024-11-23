#include "logic/cards/GrommashHellscream.h"

#include "logic/Minion.h"

const unsigned GROMMASH_HELLSCREAM_ENRAGE_ATTACK = 6;

void GrommashHellscream::on_enrage(Minion& minion) const
{
    minion.attack += GROMMASH_HELLSCREAM_ENRAGE_ATTACK;
}

void GrommashHellscream::on_no_enrage(Minion& minion) const
{
    minion.attack -= GROMMASH_HELLSCREAM_ENRAGE_ATTACK;
}