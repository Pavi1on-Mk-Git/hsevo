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

static const float CARD_TEXT_HEIGHT_RATIO = 0.06f;

void CardElement::draw_(const Game& game) const
{
    const auto& hand = to_draw(game).hand;

    if(position_ >= hand.size())
        draw_empty();
    else if(!is_player_side_)
        draw_empty(CARD_REVERSE_COLOUR);
    else
    {
        const auto& card = hand.get_card(position_);
        const auto card_rect = scaled_rect();
        const float text_height = scaled_height(CARD_TEXT_HEIGHT_RATIO);

        draw_centered_text(card->name, text_height, true);

        const raylib::Vector2 stat_rect_size(
            card_rect.width / STAT_BOX_SIZE_RATIO, card_rect.height / STAT_BOX_SIZE_RATIO
        );

        const float right_aligned_x = card_rect.x + card_rect.width - stat_rect_size.x,
                    down_aligned_y = card_rect.y + card_rect.height - stat_rect_size.y;

        const raylib::Rectangle mana_rect({right_aligned_x, card_rect.y}, stat_rect_size);

        mana_rect.Draw(MANA_COLOUR);
        draw_text(std::to_string(card->mana_cost(game)), text_height, mana_rect);

        const auto minion = dynamic_cast<const MinionCard*>(card);
        if(minion != nullptr)
        {
            const raylib::Rectangle attack_rect({card_rect.x, down_aligned_y}, stat_rect_size);

            attack_rect.Draw(ATTACK_COLOUR);
            draw_text(std::to_string(minion->base_attack), text_height, attack_rect);

            const raylib::Rectangle health_rect({right_aligned_x, down_aligned_y}, stat_rect_size);

            health_rect.Draw(HEALTH_COLOUR);
            draw_text(std::to_string(minion->base_health), text_height, health_rect);
        }
    }
}
