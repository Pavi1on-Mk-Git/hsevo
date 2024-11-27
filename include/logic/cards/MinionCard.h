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
    MinionCard(
        const char* name, unsigned base_cost, unsigned base_attack, unsigned base_health,
        const MinionKeywords& keywords, bool has_eot
    );
public:
    const unsigned base_attack, base_health;
    const MinionKeywords keywords;
    const Tribe tribe;
    bool has_deathrattle, has_eot;

    virtual ~MinionCard() = default;
    virtual std::vector<Game> on_death(const Game& prev_state, unsigned player_id) const;
    virtual void on_minion_summon(Game& game, Minion& minion, unsigned id, unsigned player_id) const;
    virtual void on_minion_damaged(Game& game, unsigned player_id) const;
    virtual void on_damaged(Game& game, unsigned player_id) const;
    virtual void on_summon(Game& game, unsigned id) const;
    virtual void on_remove(Game& game, unsigned id, unsigned player_id) const;
    virtual std::vector<Game> on_end_of_turn(const Game& prev_state, unsigned id) const;
    virtual void on_enrage(Minion& minion) const;
    virtual void on_calm_down(Minion& minion) const;
    virtual std::vector<std::unique_ptr<PlayCardAction>> create_play_actions(const Game& game, unsigned hand_position)
        const override;
};

#endif
