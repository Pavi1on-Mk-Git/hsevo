#ifndef CRUEL_TASKMASTER_H
#define CRUEL_TASKMASTER_H

#include "logic/cards/SingleArgTargetMinionMinionCard.h"

class CruelTaskmaster: public SingleArgTargetMinionMinionCard
{
private:
    CruelTaskmaster(): SingleArgTargetMinionMinionCard("Cruel Taskmaster", 2, 2, 2) {}
public:
    static const CruelTaskmaster instance;
    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;
};

inline const CruelTaskmaster CruelTaskmaster::instance;


#endif