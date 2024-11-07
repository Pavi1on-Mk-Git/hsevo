#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include <raylib-cpp.hpp>

#include "logic/Game.h"
#include "utils/GuiElementId.h"

struct GameGui;

class GuiElement
{
private:
    virtual void draw_(const Game& game) const = 0;
protected:
    static const raylib::Color TEXT_COLOUR, ACTIVE_COLOUR, INACTIVE_COLOUR, BG_COLOUR, CARD_REVERSE_COLOUR,
        ATTACK_COLOUR, HEALTH_COLOUR, MANA_COLOUR;
    static constexpr unsigned SPACING_DIVISOR = 10, STAT_BOX_SIZE_RATIO = 4;
    static constexpr float BORDER_THICKNESS = 3.f, SMALL_STAT_BOX_HEIGHT_MULTIPLIER = 1.2f;
    const GameGui& gui_;
    const bool is_player_side_;

    GuiElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side);
    void draw_bg_only(const raylib::Color& background_colour = BG_COLOUR) const;
    void draw_border() const;
    void draw_empty(const raylib::Color& background_colour = BG_COLOUR) const;
    void draw_text(
        const std::string& txt, float text_height, const raylib::Rectangle& rectangle, float offset_multiplier = 0.f
    ) const;
    void draw_centered_text(const std::string& text, float text_height, bool split_lines = false) const;
    const Player& to_draw(const Game& game) const;
    raylib::Rectangle scaled_rect() const;
    float scaled_height(float height_ratio) const;
public:
    raylib::Rectangle base_area;
    bool is_active;
    virtual GuiElementId id() const = 0;
    void draw(const Game& game) const;
};

#endif