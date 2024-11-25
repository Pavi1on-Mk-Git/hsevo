#include "logic/cards/LordJaraxxusCard.h"

#include "logic/Game.h"
#include "logic/cards/BloodFury.h"
#include "logic/heroes/LordJaraxxus.h"

std::vector<Game> LordJaraxxusCard::on_play(const Game& prev_state, const std::vector<OnPlayArg>&) const
{
    std::vector<Game> resulting_states{prev_state};
    auto& game = resulting_states.at(0);

    const bool prev_hero_active = game.current_player().hero->active;
    game.current_player().hero = std::make_unique<LordJaraxxus>();
    game.current_player().hero->active = prev_hero_active;
    game.current_player().hero->weapon = Weapon(&BloodFury::instance);

    return resulting_states;
}