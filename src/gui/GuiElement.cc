#include "gui/GuiElement.h"

#include <ranges>

#include "gui/GameGui.h"
#include "gui/utils.h"

const raylib::Color GuiElement::TEXT_COLOUR = BLACK, GuiElement::ACTIVE_COLOUR = GREEN,
                    GuiElement::INACTIVE_COLOUR = BLACK, GuiElement::BG_COLOUR = BEIGE,
                    GuiElement::ATTACK_COLOUR = YELLOW, GuiElement::CARD_REVERSE_COLOUR = DARKBLUE,
                    GuiElement::HEALTH_COLOUR = RED, GuiElement::MANA_COLOUR = BLUE;

GuiElement::GuiElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side):
    gui_(gui), is_player_side_(is_player_side), base_area(x, is_player_side ? 1.f - y - height : y, width, height),
    is_active(false)
{}

void GuiElement::draw_text(
    const std::string& txt, float text_height, const raylib::Rectangle& rectangle, float offset_multiplier
) const
{
    auto text_obj = raylib::Text(txt, text_height, TEXT_COLOUR, GetFontDefault(), text_height / SPACING_DIVISOR);

    text_obj.Draw(
        rectangle.GetPosition() +
        center_offset(rectangle.GetSize(), {static_cast<float>(text_obj.Measure()), text_height}) +
        raylib::Vector2{0.f, offset_multiplier * text_height}
    );
}

void GuiElement::draw_bg_only(const raylib::Color& background_colour) const
{
    scaled_rect().Draw(background_colour);
}

void GuiElement::draw_border() const
{
    scaled_rect().DrawLines(is_active ? ACTIVE_COLOUR : INACTIVE_COLOUR, BORDER_THICKNESS);
}

void GuiElement::draw_empty(const raylib::Color& background_colour) const
{
    draw_bg_only(background_colour);
    draw_border();
}

void GuiElement::draw_centered_text(const std::string& text, float text_height, bool split_lines) const
{
    draw_bg_only();

    const auto scaled = scaled_rect();

    if(split_lines)
    {
        auto split_text = std::views::split(text, ' ');
        const float word_count = std::ranges::distance(split_text);

        for(auto [id, range]: std::views::enumerate(split_text))
            draw_text(std::string(range.begin(), range.end()), text_height, scaled, word_count / -2 + 0.5f + id);
    }
    else
        draw_text(text, text_height, scaled);
}

const Player& GuiElement::to_draw(const Game& game) const
{
    return (gui_.is_player_turn() == is_player_side_) ? game.current_player() : game.opponent();
}

raylib::Rectangle GuiElement::scaled_rect() const
{
    return gui_.scale(base_area);
}

float GuiElement::scaled_height(float height_ratio) const
{
    return height_ratio * scaled_rect().height;
}

void GuiElement::draw(const Game& game) const
{
    draw_(game);
    draw_border();
}
