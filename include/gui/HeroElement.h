#ifndef HERO_ELEMENT_H
#define HERO_ELEMENT_H

#include "gui/GuiElement.h"

class HeroElement: public GuiElement
{
private:
    void draw_(const Game& game) const override;
public:
    HeroElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side);
    GuiElementId id() const override;
};

#endif