#ifndef CARD_H
#define CARD_H

#include <string>

#include "logic/MinionKeywords.h"

struct Card
{
    const std::string name;
    const unsigned base_mana_cost, base_attack, base_health;
    unsigned mana_cost, attack;
    int health;
    MinionKeywords keywords;
    Card(
        const std::string& name, unsigned base_cost, unsigned base_attack, unsigned base_health,
        const MinionKeywords& keywords = NO_KEYWORDS
    );
};

#endif
