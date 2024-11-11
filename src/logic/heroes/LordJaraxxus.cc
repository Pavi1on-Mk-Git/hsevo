#include "logic/heroes/LordJaraxxus.h"

#include "logic/Game.h"
#include "logic/cards/Infernal.h"

void LordJaraxxus::on_hero_power_use(Game& game, const std::vector<OnPlayArg>&)
{
    game.current_player().board.add_minion(Infernal::instance, game.current_player().board.minion_count());
}
