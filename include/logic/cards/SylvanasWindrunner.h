#ifndef SYLVANAS_WINDRUNNER_H
#define SYLVANAS_WINDRUNNER_H

#include "logic/cards/MinionCard.h"

class SylvanasWindrunner: public MinionCard
{
private:
    SylvanasWindrunner(): MinionCard("Sylvanas Windrunner", 6, 5, 5, true) {}
public:
    static const SylvanasWindrunner instance;
    std::vector<Game> on_death(const Game& prev_state, unsigned player_id) const override;
};

inline const SylvanasWindrunner SylvanasWindrunner::instance;

#endif