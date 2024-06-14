#include "GameStateInput.h"

#include <algorithm>

std::array<std::array<double, 1 + 2 * Board::MAX_BOARD_SIZE + 3>, 2> GameStateInput::get_evo_input() const
{
    std::array<std::array<double, 1 + 2 * Board::MAX_BOARD_SIZE + 3>, 2> result;
    std::transform(players.begin(), players.end(), result.begin(), [](const PlayerStateInput& player) {
        std::array<double, 1 + 2 * Board::MAX_BOARD_SIZE + 3> result_element;
        auto result_element_index = 0u;
        result_element.at(result_element_index++) = player.hero.health;
        for(const auto& minion: player.minions)
        {
            result_element.at(result_element_index++) = minion.health;
            result_element.at(result_element_index++) = minion.attack;
        }
        result_element.at(result_element_index++) = player.hand_size;
        result_element.at(result_element_index++) = player.deck_size;
        result_element.at(result_element_index++) = player.mana;
        return result_element;
    });
    return result;
}