#ifndef MINION_H
#define MINION_H

#include "logic/Entity.h"
#include "logic/MinionKeywords.h"
#include "logic/cards/MinionCard.h"

class Minion: public Entity
{
private:
    unsigned player_id_;
public:
    const MinionCard* card;
    unsigned attack, id;
    bool active, will_die_horribly, triggered_on_death, has_deathrattle;
    MinionKeywords keywords;
    std::vector<unsigned> auras_applied;

    Minion(const MinionCard* card, Game& game, unsigned player_id);
    void deal_dmg(unsigned amount, Game& game) override;
    void on_summon(Game& game, unsigned position_played);
    void on_remove(Game& game);
    std::vector<Game> on_death(Game& game);
    void on_minion_summon(Game& game, Minion& minion) const;
    void on_minion_damaged(Game& game) const;
};


#endif