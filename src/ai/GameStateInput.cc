#include "ai/GameStateInput.h"

#include <algorithm>

std::array<std::array<double, GameStateInput::INPUT_SIZE>, 2> GameStateInput::get_evo_input() const
{
    std::array<std::array<double, INPUT_SIZE>, 2> result;
    std::transform(players.begin(), players.end(), result.begin(), [](const HeroInput& player) {
        std::array<double, INPUT_SIZE> result_element;
        unsigned result_element_index = 0;
        auto add_to_element = [&](double value) { result_element.at(result_element_index++) = value; };

        add_to_element(player.hero.health);
        add_to_element(player.hero.can_attack);
        add_to_element(player.hero.weapon_attack);
        add_to_element(player.hero.weapon_durability);

        for(const auto& minion: player.minions)
        {
            add_to_element(minion.health);
            add_to_element(minion.attack);
            add_to_element(minion.can_attack);
            add_to_element(minion.has_taunt);
        }

        add_to_element(player.hand_size);
        add_to_element(player.deck_size);
        add_to_element(player.mana);

        return result_element;
    });
    return result;
}