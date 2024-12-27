#include "logic/heroes/LordJaraxxus.h"

#include "logic/Game.h"
#include "logic/cards/Infernal.h"

std::unique_ptr<Hero> LordJaraxxus::clone() const
{
    return std::make_unique<LordJaraxxus>(*this);
}

void LordJaraxxus::on_hero_power_use(Game& game)
{
    game.add_minion(&Infernal::instance, game.current_player().board.minion_count());
}
