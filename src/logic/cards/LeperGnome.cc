#include "logic/cards/LeperGnome.h"

#include "logic/Game.h"

const unsigned LEPER_GNOME_ON_DEATH_DMG = 2;

std::vector<Game> LeperGnome::on_death(Game& game, unsigned player_id) const
{
    game.players.at(1 - player_id).hero->deal_dmg(LEPER_GNOME_ON_DEATH_DMG, game);

    return {game};
}