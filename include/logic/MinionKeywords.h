#ifndef MINION_KEYWORDS_H
#define MINION_KEYWORDS_H

#include <cstdint>
#include <type_traits>

enum MinionKeywords
{
    NO_KEYWORDS = 0,
    CANT_ATTACK = 1 << 0,
    TAUNT = 1 << 1,
};

MinionKeywords& operator|=(MinionKeywords& fst, const MinionKeywords& snd);

#endif