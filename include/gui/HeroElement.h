#ifndef HERO_ELEMENT_H
#define HERO_ELEMENT_H

#include "gui/GuiElement.h"

struct HeroElement: public GuiElement
{
    HeroElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side);
    GuiElementId id() const override;
    void draw(const Game& game) const override;
};

#endif