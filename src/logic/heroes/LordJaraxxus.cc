#include "logic/heroes/LordJaraxxus.h"

#include "logic/Game.h"
#include "logic/cards/Infernal.h"

std::vector<Game> LordJaraxxus::on_hero_power_use(Game& game, const std::vector<OnPlayArg>& args)
{
    static_cast<void>(args);

    game.current_player().board.add_minion(Minion(Infernal()), game.current_player().board.minion_count());

    return {game};
}
