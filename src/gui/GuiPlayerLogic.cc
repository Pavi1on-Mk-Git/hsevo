#include "gui/GuiPlayerLogic.h"

#include <ranges>
#include <raylib-cpp.hpp>

#include "gui/GameGui.h"
#include "logic/Game.h"
#include "utils/Rng.h"

GuiPlayerLogic::GuiPlayerLogic(const Decklist& decklist, GameGui& gui): PlayerLogic(decklist), gui_(gui) {}

Game GuiPlayerLogic::choose_and_apply_action(const Game& game, std::vector<std::unique_ptr<Action>> actions)
{
    if(!IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        return game;

    auto clicked_element = gui_.mouse_position();

    if(!clicked_element)
        click_sequence_.clear();

    auto potential_sequences = GameGui::actions_to_elements(actions, click_sequence_);

    auto matching_sequence = std::ranges::find_if(potential_sequences, [&clicked_element](const auto& sequence) {
        return !sequence.empty() && (sequence.front() == *clicked_element);
    });

    if(matching_sequence == potential_sequences.end())
        click_sequence_.clear();
    else if(matching_sequence->size() == 1)
    {
        click_sequence_.clear();
        Game game_copy(game);
        auto new_states = actions.at(matching_sequence - potential_sequences.begin())->apply(game_copy);
        return new_states.at(Rng::instance().uniform_int(0, new_states.size() - 1));
    }
    else
        click_sequence_.push_back(*clicked_element);

    return game;
}