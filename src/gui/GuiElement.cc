#include "gui/GuiElement.h"

const raylib::Color GuiElement::TEXT_COLOUR = BLACK, GuiElement::ACTIVE_COLOUR = GREEN;

GuiElement::GuiElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side):
    gui_(gui), is_player_side_(is_player_side), base_area(x, is_player_side ? 1.f - y - height : y, width, height),
    is_active(false)
{}