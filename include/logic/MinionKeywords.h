#ifndef MINION_KEYWORDS_H
#define MINION_KEYWORDS_H

enum MinionKeywords
{
    NO_KEYWORDS = 0,
    CANT_ATTACK = 1 << 0,
    TAUNT = 1 << 1,
    CHARGE = 1 << 2,
};

MinionKeywords& operator|=(MinionKeywords& fst, const MinionKeywords& snd);

#endif