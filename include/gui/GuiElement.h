#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include <raylib-cpp.hpp>

#include "logic/Game.h"
#include "utils/GuiElementId.h"

struct GameGui;

class GuiElement
{
private:
    void draw_text(
        const std::string& txt, float text_height, const raylib::Rectangle& scaled, float offset_multiplier = 0.f
    ) const;
protected:
    static const raylib::Color TEXT_COLOUR, ACTIVE_COLOUR, INACTIVE_COLOUR, BG_COLOUR;
    static constexpr unsigned SPACING_DIVISOR = 10;
    static constexpr float BORDER_THICKNESS = 3.f;
    const GameGui& gui_;
    bool is_player_side_;

    GuiElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side);
    void draw_empty(const raylib::Color& background_colour = BG_COLOUR) const;
    void draw_centered_text(const std::string& text, float text_height_ratio, bool split_lines = false) const;
    const Player& to_draw(const Game& game) const;
public:
    raylib::Rectangle base_area;
    bool is_active;
    virtual GuiElementId id() const = 0;
    virtual void draw(const Game& game) const = 0;
};

#endif