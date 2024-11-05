#ifndef WEAPON_ELEMENT_H
#define WEAPON_ELEMENT_H

#include "gui/GuiElement.h"

class WeaponElement: public GuiElement
{
private:
    void draw_(const Game& game) const override;
public:
    WeaponElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side);
    GuiElementId id() const override;
};

#endif