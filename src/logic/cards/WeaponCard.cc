#include "logic/cards/WeaponCard.h"

#include "logic/Game.h"

WeaponCard::WeaponCard(const char* name, unsigned mana_cost, unsigned attack, unsigned durability):
    Card(name, mana_cost), attack(attack), durability(durability)
{}

std::vector<Game> WeaponCard::on_play(Game& game, const std::vector<OnPlayArg>&) const
{
    game.current_player().hero->weapon = Weapon(this);
    return {game};
}

void WeaponCard::on_secret_trigger(Weapon&) const {}
