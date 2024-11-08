#include "gui/MinionElement.h"

#include "gui/GameGui.h"

MinionElement::MinionElement(
    const GameGui& gui, float x, float y, float width, float height, bool is_player_side, unsigned position
): GuiElement(gui, x, y, width, height, is_player_side), position_(position)
{}

GuiElementId MinionElement::id() const
{
    return std::make_tuple(GuiElementIdType::MINION, is_player_side_, position_);
}

static const float MINION_TEXT_HEIGHT_RATIO = 0.08f;

void MinionElement::draw_(const Game& game) const
{
    const auto& board = to_draw(game).board;

    unsigned offset_position = position_;

    if(is_player_side_ && gui_.minion_gap_position)
    {
        if(*gui_.minion_gap_position == position_)
        {
            draw_empty();
            return;
        }
        else if(*gui_.minion_gap_position < position_)
            offset_position--;
    }

    if(offset_position >= board.minion_count())
        draw_empty();
    else
    {
        const auto& minion = board.get_minion(offset_position);
        const auto minion_rect = scaled_rect();
        const float number_text_height = scaled_height(MINION_TEXT_HEIGHT_RATIO) * TEXT_HEIGHT_MULTIPLIER;

        draw_centered_text(minion.name, scaled_height(MINION_TEXT_HEIGHT_RATIO), true);

        const raylib::Vector2 stat_rect_size(
            minion_rect.width / STAT_BOX_WIDTH_RATIO, minion_rect.height / STAT_BOX_HEIGHT_RATIO
        );

        const float right_aligned_x = minion_rect.x + minion_rect.width - stat_rect_size.x,
                    down_aligned_y = minion_rect.y + minion_rect.height - stat_rect_size.y;


        const raylib::Rectangle attack_rect({minion_rect.x, down_aligned_y}, stat_rect_size);

        attack_rect.Draw(ATTACK_COLOUR);
        draw_text(std::to_string(minion.attack), number_text_height, attack_rect);

        const raylib::Rectangle health_rect({right_aligned_x, down_aligned_y}, stat_rect_size);

        health_rect.Draw(HEALTH_COLOUR);
        draw_text(std::to_string(minion.health), number_text_height, health_rect);
    }
}
