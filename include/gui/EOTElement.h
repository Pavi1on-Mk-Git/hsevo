#ifndef EOT_ELEMENT_H
#define EOT_ELEMENT_H

#include "gui/GuiElement.h"

struct EOTElement: public GuiElement
{
    EOTElement(const GameGui& gui, float x, float y, float width, float height);
    GuiElementId id() const override;
    void draw(const Game& game) const override;
};

#endif