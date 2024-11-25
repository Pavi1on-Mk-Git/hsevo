#include "logic/cards/WeaponCard.h"

#include "logic/Game.h"

WeaponCard::WeaponCard(const char* name, unsigned mana_cost, unsigned attack, unsigned durability):
    Card(name, mana_cost), attack(attack), durability(durability)
{}

std::vector<Game> WeaponCard::on_play(const Game& prev_state, const std::vector<OnPlayArg>&) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    game.current_player().hero->weapon = Weapon(this);
    return resulting_states;
}

void WeaponCard::on_secret_trigger(Weapon&) const {}
