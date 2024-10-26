#ifndef GUI_UTILS_H
#define GUI_UTILS_H

#include <deque>
#include <memory>
#include <raylib-cpp.hpp>
#include <vector>

#include "logic/Action.h"
#include "utils/GuiElementId.h"

std::vector<std::deque<GuiElementId>> actions_to_elements(
    const std::vector<std::unique_ptr<Action>>& actions, const std::deque<GuiElementId>& clicked_elements
);
raylib::Vector2 center_offset(const raylib::Vector2& larger, const raylib::Vector2& smaller);

#endif