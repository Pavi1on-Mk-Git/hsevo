#ifndef AZURE_DRAKE_H
#define AZURE_DRAKE_H

#include "logic/cards/MinionCard.h"

class AzureDrake: public MinionCard
{
private:
    AzureDrake(): MinionCard("Azure Drake", 5, 4, 4, Tribe::DRAGON) {}
public:
    static const AzureDrake instance;
    std::vector<Game> on_play(const Game& prev_state, const std::vector<OnPlayArg>& args) const override;
    void on_summon(Game& game, unsigned id) const override;
    void on_remove(Game& game, unsigned id, unsigned player_id) const override;
};

inline const AzureDrake AzureDrake::instance;

#endif