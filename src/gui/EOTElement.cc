#include "gui/EOTElement.h"

EOTElement::EOTElement(const GameGui& gui, float x, float y, float width, float height):
    GuiElement(gui, x, y, width, height, true)
{}

GuiElementId EOTElement::id() const
{
    return GuiElementIdType::EOT_BUTTON;
}

static const float EOT_TEXT_HEIGHT_RATIO = 0.3f;

void EOTElement::draw_(const Game&) const
{
    draw_centered_text("END OF TURN", scaled_height(EOT_TEXT_HEIGHT_RATIO));
}