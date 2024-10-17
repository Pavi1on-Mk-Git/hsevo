#include "logic/cards/LordJaraxxusCard.h"

#include "logic/Game.h"
#include "logic/heroes/LordJaraxxus.h"

std::vector<Game> LordJaraxxusCard::on_play(Game& game, const std::vector<OnPlayArg>&) const
{
    game.current_player().hero = std::make_unique<LordJaraxxus>();
    game.current_player().hero->weapon = Weapon("Blood Fury", 3, 8);

    return {game};
}