#include "gui/CardElement.h"

#include "gui/GameGui.h"

CardElement::CardElement(
    const GameGui& gui, float x, float y, float width, float height, bool is_player_side, unsigned position
): GuiElement(gui, x, y, width, height, is_player_side), position_(position)
{}

GuiElementId CardElement::id() const
{
    return std::make_tuple(GuiElementIdType::CARD, is_player_side_, position_);
}

static const raylib::Color CARD_REVERSE_COLOUR = DARKBLUE;
static const float CARD_HEIGHT_RATIO = 0.06f;

void CardElement::draw(const Game& game) const
{
    const auto& hand = to_draw(game).hand;

    if(position_ >= hand.size())
        draw_empty();
    else if(!is_player_side_)
        draw_empty(DARKBLUE);
    else
        draw_centered_text(hand.get_card(position_)->name, CARD_HEIGHT_RATIO, true);
}