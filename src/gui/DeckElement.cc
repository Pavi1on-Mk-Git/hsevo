#include "gui/DeckElement.h"

#include <format>

DeckElement::DeckElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side):
    GuiElement(gui, x, y, width, height, is_player_side)
{}

GuiElementId DeckElement::id() const
{
    return std::make_pair(GuiElementIdType::OTHER, is_player_side_);
}

static const float DECK_TEXT_HEIGHT_RATIO = 0.4f, MANA_TEXT_BOX_WIDTH_MULTIPLIER = 1.5f;
static const unsigned MANA_TEXT_HEIGHT_DIVISOR = 4;

void DeckElement::draw_(const Game& game) const
{
    const auto& player = to_draw(game);

    const auto& deck = player.deck;

    auto deck_rect = scaled_rect();
    unsigned text_height = scaled_height(DECK_TEXT_HEIGHT_RATIO);

    draw_centered_text(std::to_string(deck.size()), text_height);

    const raylib::Vector2 stat_rect_size(
        deck_rect.width * MANA_TEXT_BOX_WIDTH_MULTIPLIER / STAT_BOX_WIDTH_RATIO,
        deck_rect.height / STAT_BOX_HEIGHT_RATIO
    );

    const raylib::Rectangle mana_rect({deck_rect.x, deck_rect.y + deck_rect.height - stat_rect_size.y}, stat_rect_size);

    mana_rect.Draw(MANA_COLOUR);
    draw_text(
        std::format("{}/{}", player.mana, player.mana_crystals), text_height / MANA_TEXT_HEIGHT_DIVISOR, mana_rect
    );
}