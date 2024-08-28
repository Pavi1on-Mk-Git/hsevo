#ifndef MINION_CARD_H
#define MINION_CARD_H

#include <memory>
#include <string>

#include "logic/MinionKeywords.h"
#include "logic/Tribe.h"
#include "logic/cards/Card.h"

class MinionCard: public Card
{
protected:
    MinionCard(std::string_view name, unsigned base_cost, unsigned base_attack, unsigned base_health);
    MinionCard(
        std::string_view name, unsigned base_cost, unsigned base_attack, unsigned base_health,
        const MinionKeywords& keywords
    );
    MinionCard(
        std::string_view name, unsigned base_cost, unsigned base_attack, unsigned base_health, const Tribe& tribe
    );
public:
    const unsigned base_attack, base_health;
    MinionKeywords keywords;
    Tribe tribe;

    virtual ~MinionCard() = default;
    virtual std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position);
};

#endif
