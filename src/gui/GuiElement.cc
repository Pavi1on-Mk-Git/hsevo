#include "gui/GuiElement.h"

#include <ranges>

#include "gui/GameGui.h"
#include "gui/utils.h"

const raylib::Color GuiElement::TEXT_COLOUR = BLACK, GuiElement::ACTIVE_COLOUR = GREEN,
                    GuiElement::INACTIVE_COLOUR = BLACK, GuiElement::BG_COLOUR = BEIGE;

GuiElement::GuiElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side):
    gui_(gui), is_player_side_(is_player_side), base_area(x, is_player_side ? 1.f - y - height : y, width, height),
    is_active(false)
{}

void GuiElement::draw_text(
    const std::string& txt, float text_height, const raylib::Rectangle& scaled, float offset_multiplier
) const
{
    auto text_obj = raylib::Text(txt, text_height, TEXT_COLOUR, GetFontDefault(), text_height / SPACING_DIVISOR);

    text_obj.Draw(
        scaled.GetPosition() + center_offset(scaled.GetSize(), {static_cast<float>(text_obj.Measure()), text_height}) +
        raylib::Vector2{0.f, offset_multiplier * text_height}
    );
}

void GuiElement::draw_centered_text(const std::string& text, float text_height_ratio, bool split_lines) const
{
    const auto scaled = gui_.scale(base_area);
    const auto text_height = text_height_ratio * scaled.height;

    scaled.Draw(BG_COLOUR);
    scaled.DrawLines(is_active ? ACTIVE_COLOUR : INACTIVE_COLOUR, BORDER_THICKNESS);

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
