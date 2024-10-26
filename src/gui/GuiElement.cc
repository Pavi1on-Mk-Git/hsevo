#include "gui/GuiElement.h"

#include "gui/GameGui.h"
#include "gui/utils.h"

const raylib::Color GuiElement::TEXT_COLOUR = BLACK, GuiElement::ACTIVE_COLOUR = GREEN,
                    GuiElement::INACTIVE_COLOUR = BLACK, GuiElement::BG_COLOUR = BEIGE;

GuiElement::GuiElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side):
    gui_(gui), is_player_side_(is_player_side), base_area(x, is_player_side ? 1.f - y - height : y, width, height),
    is_active(false)
{}

void GuiElement::draw_centered_text(const std::string& text, float text_height_ratio) const
{
    const auto scaled = gui_.scale(base_area);
    const auto text_height = text_height_ratio * scaled.height;

    raylib::Text text_obj(text, text_height, TEXT_COLOUR, GetFontDefault(), text_height / SPACING_DIVISOR);

    scaled.Draw(BG_COLOUR);

    scaled.DrawLines(is_active ? ACTIVE_COLOUR : INACTIVE_COLOUR, BORDER_THICKNESS);

    text_obj.Draw(
        scaled.GetPosition() + center_offset(scaled.GetSize(), {static_cast<float>(text_obj.Measure()), text_height})
    );
}
