#include "gui/DeckElement.h"

#include "gui/GameGui.h"

DeckElement::DeckElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side):
    GuiElement(gui, x, y, width, height, is_player_side)
{}

GuiElementId DeckElement::id() const
{
    return std::make_pair(GuiElementIdType::OTHER, is_player_side_);
}

static const float DECK_TEXT_HEIGHT_RATIO = 0.6f;

void DeckElement::draw(const Game& game) const
{
    const auto& deck = to_draw(game).deck;

    draw_centered_text(std::to_string(deck.size()), DECK_TEXT_HEIGHT_RATIO);
}