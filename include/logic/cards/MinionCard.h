#ifndef MINION_CARD_H
#define MINION_CARD_H

#include <memory>

#include "logic/MinionKeywords.h"
#include "logic/Tribe.h"
#include "logic/cards/Card.h"

struct Minion;

class MinionCard: public Card
{
protected:
    MinionCard(const char* name, unsigned base_cost, unsigned base_attack, unsigned base_health);
    MinionCard(
        const char* name, unsigned base_cost, unsigned base_attack, unsigned base_health, const MinionKeywords& keywords
    );
    MinionCard(const char* name, unsigned base_cost, unsigned base_attack, unsigned base_health, const Tribe& tribe);
    MinionCard(const char* name, unsigned base_cost, unsigned base_attack, unsigned base_health, bool has_deathrattle);
    MinionCard(
        const char* name, unsigned base_cost, unsigned base_attack, unsigned base_health,
        const MinionKeywords& keywords, const Tribe& tribe
    );
public:
    const unsigned base_attack, base_health;
    const MinionKeywords keywords;
    const Tribe tribe;
    bool has_deathrattle;

    virtual ~MinionCard() = default;
    virtual std::vector<Game> on_death(Game& game, unsigned player_id) const;
    virtual void on_minion_summon(Game& game, Minion& minion, unsigned id, unsigned player_id) const;
    virtual void on_minion_damaged(Game& game, unsigned player_id) const;
    virtual void on_damaged(Game& game, unsigned player_id) const;
    virtual void on_summon(Game& game, unsigned position_played) const;
    virtual void on_remove(Game& game, unsigned id, unsigned player_id) const;
    virtual std::vector<Game> on_end_of_turn(Game& game, unsigned id, unsigned player_id) const;
    virtual std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position)
        const override;
};

#endif
