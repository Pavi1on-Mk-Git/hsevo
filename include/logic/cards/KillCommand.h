#ifndef KILL_COMMAND_H
#define KILL_COMMAND_H

#include "logic/cards/SingleArgTargetCard.h"

class KillCommand: public SingleArgTargetCard
{
private:
    KillCommand(): SingleArgTargetCard("Kill Command", 3) {}
public:
    static const KillCommand instance;
    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;
};

inline const KillCommand KillCommand::instance;

#endif