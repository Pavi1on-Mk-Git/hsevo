#include "logic/Minion.h"

#include "logic/Game.h"

Minion::Minion(const MinionCard* card, Game& game, unsigned player_id):
    Entity(card->name, card->base_health, card->tribe), player_id_(player_id), card_(card), attack(card->base_attack),
    id(game.next_minion_id()), active(card->keywords & CHARGE), will_die_horribly(false), triggered_on_death(false),
    has_deathrattle(card->has_deathrattle), keywords(card->keywords)
{}

std::vector<Game> Minion::on_death(Game& game)
{
    return card_->on_death(game, player_id_);
}
