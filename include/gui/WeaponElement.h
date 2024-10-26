#ifndef WEAPON_ELEMENT_H
#define WEAPON_ELEMENT_H

#include "gui/GuiElement.h"

struct WeaponElement: public GuiElement
{
    WeaponElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side);
    GuiElementId id() const override;
    void draw(const Game& game) const override;
};

#endif