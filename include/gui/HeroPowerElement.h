#ifndef HERO_POWER_ELEMENT_H
#define HERO_POWER_ELEMENT_H

#include "gui/GuiElement.h"

/**
 * Gui element used for drawing player's hero power
 */
class HeroPowerElement: public GuiElement
{
private:
    void draw_(const Game& game) const override;
public:
    HeroPowerElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side);
    GuiElementId id() const override;
};

#endif