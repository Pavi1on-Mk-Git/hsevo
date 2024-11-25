#ifndef CAIRNE_BLOODHOOF_H
#define CAIRNE_BLOODHOOF_H

#include "logic/cards/MinionCard.h"

class CairneBloodhoof: public MinionCard
{
private:
    CairneBloodhoof(): MinionCard("Cairne Bloodhoof", 6, 4, 5, true) {}
public:
    static const CairneBloodhoof instance;
    std::vector<Game> on_death(const Game& prev_state, unsigned player_id) const override;
};

inline const CairneBloodhoof CairneBloodhoof::instance;

#endif