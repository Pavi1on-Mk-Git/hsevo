#ifndef MINION_H
#define MINION_H

#include "logic/Entity.h"
#include "logic/MinionKeywords.h"
#include "logic/cards/MinionCard.h"

class Minion: public Entity
{
private:
    unsigned player_id_;
    const MinionCard* card_;
public:
    unsigned attack, id;
    bool active, will_die_horribly, triggered_on_death, has_deathrattle;
    MinionKeywords keywords;
    std::vector<unsigned> auras_applied;
    Minion(const MinionCard* card, Game& game, unsigned player_id);
    std::vector<Game> on_death(Game& game);
    void on_minion_summon(Game& game, Minion& minion);
};


#endif