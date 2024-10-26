#include "gui/utils.h"

#include <algorithm>
#include <ranges>

std::vector<std::deque<GuiElementId>> actions_to_elements(
    const std::vector<std::unique_ptr<Action>>& actions, const std::deque<GuiElementId>& clicked_elements
)
{
    std::vector<std::deque<GuiElementId>> element_sequences;

    for(const auto& action: actions)
    {
        std::deque<GuiElementId> gui_elements = action->element_sequence();

        if((gui_elements.size() < clicked_elements.size()) ||
           !std::ranges::all_of(std::views::zip(gui_elements, clicked_elements), [](const auto& expected_and_clicked) {
               return expected_and_clicked.first == expected_and_clicked.second;
           }))
            element_sequences.emplace_back();
        else
            element_sequences.emplace_back(gui_elements.begin() + clicked_elements.size(), gui_elements.end());
    }

    return element_sequences;
}

raylib::Vector2 center_offset(const raylib::Vector2& larger, const raylib::Vector2& smaller)
{
    return {
        (larger.x - smaller.x) / 2,
        (larger.y - smaller.y) / 2,
    };
}
