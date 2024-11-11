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
    bool active, will_die_horribly, triggered_on_death;
    MinionKeywords keywords;
    Minion(const MinionCard* card, Game& game, unsigned player_id);
    std::vector<Game> on_death(Game& game);
};


#endif