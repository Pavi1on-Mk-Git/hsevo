#ifndef TIMBER_WOLF_H
#define TIMBER_WOLF_H

#include "logic/Minion.h"
#include "logic/cards/SingleArgSelfPlayPositionCard.h"

class TimberWolf: public SingleArgSelfPlayPositionCard
{
private:
    TimberWolf(): SingleArgSelfPlayPositionCard("Timber Wolf", 1, 1, 1, Tribe::BEAST) {}
public:
    static const TimberWolf instance;
    std::vector<Game> on_play(Game& game, const std::vector<OnPlayArg>& args) const override;
    std::vector<Game> on_death(Game& game, unsigned id, unsigned player_id) const override;
    void on_minion_summon(Game& game, Minion& minion, unsigned id, unsigned player_id) const override;
};

inline const TimberWolf TimberWolf::instance;

#endif