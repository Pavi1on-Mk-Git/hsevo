#include "gui/DiscoverElement.h"

#include "gui/GameGui.h"

DiscoverElement::DiscoverElement(
    const GameGui& gui, float x, float y, float width, float height, unsigned position, Game& game
): GuiElement(gui, x, y, width, height, true), position_(position), game_(game)
{}

GuiElementId DiscoverElement::id() const
{
    return std::make_pair(GuiElementIdType::DISCOVER, position_);
}

static const float CARD_TEXT_HEIGHT_RATIO = 0.07f;

void DiscoverElement::draw_(const Game&) const
{
    if(!gui_.is_in_discover_mode || to_draw(game_).deck.size() <= position_)
        return;

    const auto& deck = to_draw(game_).deck;

    const auto& card = deck.peek(position_);
    const auto card_rect = scaled_rect();
    const float number_text_height = scaled_height(CARD_TEXT_HEIGHT_RATIO) * TEXT_HEIGHT_MULTIPLIER;

    draw_centered_text(card->name, scaled_height(CARD_TEXT_HEIGHT_RATIO), true);

    const raylib::Vector2 stat_rect_size(
        card_rect.width / STAT_BOX_WIDTH_RATIO, card_rect.height / STAT_BOX_HEIGHT_RATIO
    );

    const float right_aligned_x = card_rect.x + card_rect.width - stat_rect_size.x,
                down_aligned_y = card_rect.y + card_rect.height - stat_rect_size.y;

    const raylib::Rectangle mana_rect({right_aligned_x, card_rect.y}, stat_rect_size);

    mana_rect.Draw(MANA_COLOUR);
    draw_text(std::to_string(card->mana_cost(game_)), number_text_height, mana_rect);

    const auto minion = dynamic_cast<const MinionCard*>(card);
    if(minion != nullptr)
    {
        const raylib::Rectangle attack_rect({card_rect.x, down_aligned_y}, stat_rect_size);

        attack_rect.Draw(ATTACK_COLOUR);
        draw_text(std::to_string(minion->base_attack), number_text_height, attack_rect);

        const raylib::Rectangle health_rect({right_aligned_x, down_aligned_y}, stat_rect_size);

        health_rect.Draw(HEALTH_COLOUR);
        draw_text(std::to_string(minion->base_health), number_text_height, health_rect);
    }
}

void DiscoverElement::draw_border() const
{
    if(gui_.is_in_discover_mode && to_draw(game_).deck.size() > position_)
        GuiElement::draw_border();
}