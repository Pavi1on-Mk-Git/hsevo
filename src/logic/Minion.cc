#include "logic/Minion.h"

#include "logic/Game.h"

Minion::Minion(const MinionCard* card, Game& game, unsigned player_id):
    Entity(card->name, card->base_health, card->tribe), card(card), attack(card->base_attack),
    id(game.next_minion_id()), player_id(player_id), active(card->keywords & CHARGE), will_die_horribly(false),
    has_deathrattle(card->has_deathrattle), keywords(card->keywords)
{}

void Minion::restore_health(unsigned amount)
{
    health = std::min(max_health, health + amount);
    if(static_cast<unsigned>(health) == max_health)
        card->on_calm_down(*this);
}

void Minion::deal_dmg(unsigned amount, Game& game)
{
    if(static_cast<unsigned>(health) == max_health)
        card->on_enrage(*this);

    health -= amount;

    card->on_damaged(game, player_id);

    for(const auto& minion: game.players.at(player_id).board)
        minion.on_minion_damaged(game);
}

void Minion::on_summon(Game& game, unsigned position_played) const
{
    card->on_summon(game, position_played);
}

void Minion::on_remove(Game& game) const
{
    card->on_remove(game, id, player_id);
}

std::vector<Game> Minion::on_death(Game& game) const
{
    return card->on_death(game, player_id);
}

void Minion::on_minion_summon(Game& game, Minion& minion) const
{
    card->on_minion_summon(game, minion, id, player_id);
}

void Minion::on_minion_damaged(Game& game) const
{
    card->on_minion_damaged(game, player_id);
}

std::vector<Game> Minion::on_end_of_turn(Game& game)
{
    if(will_die_horribly)
        health = 0;

    return card->on_end_of_turn(game, id);
}
