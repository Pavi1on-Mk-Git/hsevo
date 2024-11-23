#include "logic/Minion.h"

#include "logic/Game.h"

Minion::Minion(const MinionCard* card, Game& game, unsigned player_id):
    Entity(card->name, card->base_health, card->tribe), player_id_(player_id), card(card), attack(card->base_attack),
    id(game.next_minion_id()), active(card->keywords & CHARGE), will_die_horribly(false), triggered_on_death(false),
    has_deathrattle(card->has_deathrattle), keywords(card->keywords)
{}

void Minion::deal_dmg(unsigned amount, Game& game)
{
    health -= amount;

    card->on_damaged(game, player_id_);

    for(const auto& minion: game.players.at(player_id_).board)
        minion.on_minion_damaged(game);
}

void Minion::on_summon(Game& game, unsigned position_played)
{
    card->on_summon(game, position_played);
}

void Minion::on_remove(Game& game)
{
    card->on_remove(game, id, player_id_);
}

std::vector<Game> Minion::on_death(Game& game)
{
    return card->on_death(game, player_id_);
}

void Minion::on_minion_summon(Game& game, Minion& minion) const
{
    card->on_minion_summon(game, minion, id, player_id_);
}

void Minion::on_minion_damaged(Game& game) const
{
    card->on_minion_damaged(game, player_id_);
}
