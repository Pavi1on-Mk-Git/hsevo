#ifndef TIMBER_WOLF_H
#define TIMBER_WOLF_H

#include "logic/Minion.h"
#include "logic/cards/SingleArgSelfPlayPositionMinionCard.h"

class TimberWolf: public SingleArgSelfPlayPositionMinionCard
{
private:
    TimberWolf(): SingleArgSelfPlayPositionMinionCard("Timber Wolf", 1, 1, 1, Tribe::BEAST) {}
public:
    static const TimberWolf instance;
    void on_minion_summon(Game& game, Minion& minion, unsigned id, unsigned player_id) const override;
    void on_summon(Game& game, unsigned id) const override;
    void on_remove(Game& game, unsigned id, unsigned player_id) const override;
};

inline const TimberWolf TimberWolf::instance;

#endif