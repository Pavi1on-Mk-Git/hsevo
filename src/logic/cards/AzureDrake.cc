#include "logic/cards/AzureDrake.h"

#include "logic/Game.h"

std::vector<Game> AzureDrake::on_play(const Game& prev_state, const std::vector<OnPlayArg>&) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);
    game.draw();

    return resulting_states;
}

const unsigned AZURE_DRAKE_SPELL_DMG = 1;

void AzureDrake::on_summon(Game& game, unsigned) const
{
    game.current_player().spell_damage += AZURE_DRAKE_SPELL_DMG;
}

void AzureDrake::on_remove(Game& game, unsigned, unsigned player_id) const
{
    game.players.at(player_id).spell_damage -= AZURE_DRAKE_SPELL_DMG;
}
