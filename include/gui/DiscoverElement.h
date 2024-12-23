#ifndef DISCOVER_ELEMENT_H
#define DISCOVER_ELEMENT_H

#include "gui/GuiElement.h"

class DiscoverElement: public GuiElement
{
private:
    unsigned position_;
    Game& game_;
    void draw_(const Game& game) const override;
    void draw_border() const override;
public:
    DiscoverElement(const GameGui& gui, float x, float y, float width, float height, unsigned position, Game& game);
    GuiElementId id() const override;
};

#endif