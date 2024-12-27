#ifndef DISCOVER_ELEMENT_H
#define DISCOVER_ELEMENT_H

#include "gui/GuiElement.h"

/**
 * Gui element used for drawing a card while using discover mechanic
 */
class DiscoverElement: public GuiElement
{
private:
    /**
     * Position of the card being discovered
     */
    unsigned position_;

    /**
     * Reference to the game instance from which the discover data will be taken
     */
    Game& game_;
    void draw_(const Game& game) const override;
    void draw_border() const override;
public:
    DiscoverElement(const GameGui& gui, float x, float y, float width, float height, unsigned position, Game& game);
    GuiElementId id() const override;
};

#endif