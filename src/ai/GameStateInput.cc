#include "ai/GameStateInput.h"

#include <algorithm>

std::array<std::array<double, GameStateInput::INPUT_SIZE>, 2> GameStateInput::get_evo_input() const
{
    std::array<std::array<double, INPUT_SIZE>, 2> result;
    std::ranges::transform(players, result.begin(), [](const PlayerInput& player) {
        std::array<double, INPUT_SIZE> result_element;
        auto result_element_it = result_element.begin();
        auto add_to_element = [&](double value) { *result_element_it++ = value; };

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
            add_to_element(minion.has_deathrattle);
            add_to_element(minion.has_eot);
        }

        add_to_element(player.hand_size);
        add_to_element(player.deck_size);
        add_to_element(player.mana);
        add_to_element(player.secret_count);

        return result_element;
    });
    return result;
}
