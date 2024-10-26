#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include <raylib-cpp.hpp>

#include "logic/Game.h"
#include "utils/GuiElementId.h"

struct GameGui;

class GuiElement
{
protected:
    static const raylib::Color TEXT_COLOUR, ACTIVE_COLOUR;
    static constexpr unsigned SPACING_DIVISOR = 10;
    static constexpr float BORDER_THICKNESS = 5.f;
    const GameGui& gui_;
    bool is_player_side_;

    GuiElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side);
public:
    raylib::Rectangle base_area;
    bool is_active;
    virtual GuiElementId id() const = 0;
    virtual void draw(const Game& game) const = 0;
};

#endif