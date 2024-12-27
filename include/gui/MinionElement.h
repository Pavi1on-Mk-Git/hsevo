#ifndef MINION_ELEMENT_H
#define MINION_ELEMENT_H

#include "gui/GuiElement.h"

/**
 * Gui element used for drawing a minion
 */
class MinionElement: public GuiElement
{
private:
    /**
     * Minion's position on the board
     */
    unsigned position_;
    void draw_(const Game& game) const override;
public:
    MinionElement(
        const GameGui& gui, float x, float y, float width, float height, bool is_player_side, unsigned position
    );
    GuiElementId id() const override;
};

#endif