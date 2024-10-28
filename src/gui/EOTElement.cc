#include "gui/EOTElement.h"

EOTElement::EOTElement(const GameGui& gui, float x, float y, float width, float height):
    GuiElement(gui, x, y, width, height, true)
{}

GuiElementId EOTElement::id() const
{
    return GuiElementIdType::EOT_BUTTON;
}

static const float EOT_TEXT_HEIGHT_RATIO = 0.4f;

void EOTElement::draw(const Game&) const
{
    draw_centered_text("END OF TURN", EOT_TEXT_HEIGHT_RATIO);
}