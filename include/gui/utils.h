#ifndef GUI_UTILS_H
#define GUI_UTILS_H

#include <deque>
#include <memory>
#include <raylib-cpp.hpp>
#include <vector>

#include "logic/Action.h"
#include "utils/GuiElementId.h"

/**
 * Convert a vector of actions to a vector of click sequences necessary to do those actions given the current sequence
 * of clicks
 * @param actions Possible actions
 * @param clicked_elements Elements already clicked by the user
 * @return Vector of click sequences necessary to finish each of the possible actions
 */
std::vector<std::deque<GuiElementId>> actions_to_elements(
    const std::vector<std::unique_ptr<Action>>& actions, const std::deque<GuiElementId>& clicked_elements
);

/**
 * Return coordinates for a rectangle of size `smaller` which would place it at the center of a rectangle with size
 * `larger`
 * @param larger Size of the larger rectangle
 * @param smaller Size of the smaller rectangle
 * @return Center point for the smaller rectangle
 */
raylib::Vector2 center_offset(const raylib::Vector2& larger, const raylib::Vector2& smaller);

#endif