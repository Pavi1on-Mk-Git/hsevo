#ifndef EOT_ELEMENT_H
#define EOT_ELEMENT_H

#include "gui/GuiElement.h"

class EOTElement: public GuiElement
{
private:
    void draw_(const Game& game) const override;
public:
    EOTElement(const GameGui& gui, float x, float y, float width, float height);
    GuiElementId id() const override;
};

#endif