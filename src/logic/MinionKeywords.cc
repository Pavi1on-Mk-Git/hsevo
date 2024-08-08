#include "logic/MinionKeywords.h"

MinionKeywords& operator|=(MinionKeywords& fst, const MinionKeywords& snd)
{
    return fst = static_cast<MinionKeywords>(fst | snd);
}
