#ifndef MINION_ELEMENT_H
#define MINION_ELEMENT_H

#include "gui/GuiElement.h"

class MinionElement: public GuiElement
{
private:
    unsigned position_;
public:
    MinionElement(
        const GameGui& gui, float x, float y, float width, float height, bool is_player_side, unsigned position
    );
    GuiElementId id() const override;
    void draw(const Game& game) const override;
};

#endif