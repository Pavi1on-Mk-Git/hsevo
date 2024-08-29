#include "logic/cards/Card.h"

#include "logic/Game.h"

Card::Card(std::string_view name, unsigned base_cost): mana_cost_(base_cost), name(name) {}

unsigned Card::mana_cost(const Game& game) const
{
    static_cast<void>(game);

    return mana_cost_;
}

void Card::on_play(Game& game, const std::vector<OnPlayArg>& args)
{
    static_cast<void>(game);
    static_cast<void>(args);
}