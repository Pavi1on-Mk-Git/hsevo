#ifndef MINION_H
#define MINION_H

#include "logic/Entity.h"
#include "logic/MinionKeywords.h"
#include "logic/cards/MinionCard.h"

struct Minion: public Entity
{
    const MinionCard* card;
    unsigned attack, id, player_id;
    bool active, will_die_horribly, has_deathrattle;
    MinionKeywords keywords;
    std::vector<unsigned> auras_applied;

    Minion(const MinionCard* card, Game& game, unsigned player_id);
    void restore_health(unsigned amount);
    void deal_dmg(unsigned amount, Game& game) override;
    void on_summon(Game& game, unsigned position_played) const;
    void on_remove(Game& game) const;
    std::vector<Game> on_death(Game& game) const;
    void on_minion_summon(Game& game, Minion& minion) const;
    void on_minion_damaged(Game& game) const;
    std::vector<Game> on_end_of_turn(Game& game);
};


#endif