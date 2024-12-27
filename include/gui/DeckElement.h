#ifndef DECK_ELEMENT_H
#define DECK_ELEMENT_H

#include "gui/GuiElement.h"

/**
 * Gui element used for drawing a card deck
 */
class DeckElement: public GuiElement
{
private:
    void draw_(const Game& game) const override;
public:
    DeckElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side);
    GuiElementId id() const override;
};

#endif