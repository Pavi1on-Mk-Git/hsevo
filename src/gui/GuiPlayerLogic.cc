#include "gui/GuiPlayerLogic.h"

#include <ranges>
#include <raylib-cpp.hpp>

#include "gui/GameGui.h"
#include "gui/utils.h"
#include "logic/Game.h"

GuiPlayerLogic::GuiPlayerLogic(const Decklist& decklist, GameGui& gui, Rng& rng):
    PlayerLogic(decklist), gui_(gui), rng_(rng)
{}

Game GuiPlayerLogic::choose_and_apply_action(const Game& game, const std::vector<std::unique_ptr<Action>>& actions)
    const
{
    auto potential_sequences = actions_to_elements(actions, click_sequence_);

    gui_.make_active(potential_sequences);

    if(!IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        return game;

    auto clicked_element = gui_.clicked_element();

    if(!clicked_element)
        return game;

    auto matching_sequence = std::ranges::find_if(potential_sequences, [&clicked_element](const auto& sequence) {
        return !sequence.empty() && (sequence.front() == *clicked_element);
    });

    if(matching_sequence == potential_sequences.end())
    {
        click_sequence_.clear();
        gui_.minion_gap_position = std::nullopt;
    }
    else if(matching_sequence->size() == 1)
    {
        click_sequence_.clear();
        gui_.minion_gap_position = std::nullopt;
        gui_.is_in_discover_mode = false;
        auto new_states = actions.at(matching_sequence - potential_sequences.begin())->apply(game);
        return new_states.at(rng_.uniform_int(0, new_states.size() - 1));
    }
    else
    {
        click_sequence_.push_back(*clicked_element);

        // Used to make it so that Gui knows how to offset drawing minions
        if(std::holds_alternative<GuiElementIdWithPosition>(*clicked_element) && click_sequence_.size() == 2)
        {
            const auto& [type, is_player_side, position] = std::get<GuiElementIdWithPosition>(*clicked_element);
            if(type == GuiElementIdType::MINION)
                gui_.minion_gap_position = position;
        }
    }

    return game;
}