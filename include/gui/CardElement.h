#ifndef CARD_ELEMENT_H
#define CARD_ELEMENT_H

#include "gui/GuiElement.h"

/**
 * Gui element used for drawing a card
 */
class CardElement: public GuiElement
{
private:
    /**
     * Card's position in hand
     */
    unsigned position_;
    void draw_(const Game& game) const override;
public:
    CardElement(
        const GameGui& gui, float x, float y, float width, float height, bool is_player_side, unsigned position
    );
    GuiElementId id() const override;
};

#endif