#include "logic/cards/LeperGnome.h"

#include "logic/Game.h"

const unsigned LEPER_GNOME_ON_DEATH_DMG = 2;

std::vector<Game> LeperGnome::on_death(const Game& prev_state, unsigned player_id) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    game.players.at(1 - player_id).hero->deal_dmg(LEPER_GNOME_ON_DEATH_DMG, game);

    return resulting_states;
}