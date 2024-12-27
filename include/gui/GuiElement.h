#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include <raylib-cpp.hpp>

#include "logic/Game.h"
#include "utils/GuiElementId.h"

struct GameGui;

/**
 * Base clas for an element drawn in the game gui
 */
class GuiElement
{
private:
    /**
     * Draw the element
     * @param game Game state
     */
    virtual void draw_(const Game& game) const = 0;
protected:
    /**
     * Various colour constants used for drawing
     */
    static const raylib::Color TEXT_COLOUR, ACTIVE_COLOUR, INACTIVE_COLOUR, BG_COLOUR, CARD_REVERSE_COLOUR,
        ATTACK_COLOUR, HEALTH_COLOUR, MANA_COLOUR;

    /**
     * Various constants used for controlling element and text position and spacing
     */
    static constexpr unsigned SPACING_DIVISOR = 10, STAT_BOX_WIDTH_RATIO = 4, STAT_BOX_HEIGHT_RATIO = 6;

    /**
     * Various constants used for controlling element and text position and spacing
     */
    static constexpr float BORDER_THICKNESS = 3.f, TEXT_HEIGHT_MULTIPLIER = 1.5f;

    /**
     * Gui containing the element
     */
    const GameGui& gui_;

    /**
     * Flag signaling whether the element is on the player or bot side of the screen
     */
    const bool is_player_side_;

    /**
     * Construct a gui element
     * @param gui Gui containing the element
     * @param x Horizontal position of the element
     * @param y Vertical position of the element
     * @param width Width of the element
     * @param height Height of the element
     * @param is_player_side Flag signaling whether the element is on the player or bot side of the screen
     */
    GuiElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side);

    /**
     * Draw background of the element
     * @param background_colour Colour of the background
     */
    void draw_bg_only(const raylib::Color& background_colour = BG_COLOUR) const;

    /**
     * Draw border of the element
     */
    virtual void draw_border() const;

    /**
     * Draw element background and border
     * @param background_colour Colour of the background
     */
    void draw_empty(const raylib::Color& background_colour = BG_COLOUR) const;

    /**
     * Draw text in the center of the provided rectangle
     * @param txt Text to draw
     * @param text_height Height of the text
     * @param rectangle Rectangle to draw the text in
     * @param offset_multiplier How much to offset the text vertically from the center of the rectangle
     */
    void draw_text(
        const std::string& txt, float text_height, const raylib::Rectangle& rectangle, float offset_multiplier = 0.f
    ) const;

    /**
     * Draw text in the center of the element
     * @param text Text to draw
     * @param text_height Height of the text
     * @param split_lines Whether to split the text into multiple lines
     */
    void draw_centered_text(const std::string& text, float text_height, bool split_lines = false) const;

    /**
     * Return the player object which should be used to draw the element
     * @param game Game state from which the player instance will be taken
     * @return Player instance
     */
    const Player& to_draw(const Game& game) const;

    /**
     * Return rectangle containing the element scaled to the dimensions of the window in which it is placed
     * @return Scaled rectangle
     */
    raylib::Rectangle scaled_rect() const;

    /**
     * Scale provided height to the dimensions of the window in which the element is placed
     * @param height_ratio Height to scale
     * @return Scaled height
     */
    float scaled_height(float height_ratio) const;
public:
    /**
     * Rectangle containing the element with dimensions represented in percentages
     */
    raylib::Rectangle base_area;

    /**
     * Flag signaling if the element is currently active
     */
    bool is_active;

    /**
     * Return id of the element
     * @return Id of the element
     */
    virtual GuiElementId id() const = 0;

    /**
     * Draw the element
     * @param game Game state from which the element data is taken
     */
    void draw(const Game& game) const;
};

#endif