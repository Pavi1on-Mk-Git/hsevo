#include "gui/MinionElement.h"

MinionElement::MinionElement(
    const GameGui& gui, float x, float y, float width, float height, bool is_player_side, unsigned position
): GuiElement(gui, x, y, width, height, is_player_side), position_(position)
{}

GuiElementId MinionElement::id() const
{
    return std::make_tuple(GuiElementIdType::MINION, is_player_side_, position_);
}

static const float MINION_TEXT_HEIGHT_RATIO = 0.08f;

void MinionElement::draw(const Game& game) const
{
    const auto& board = to_draw(game).board;

    if(position_ >= board.minion_count())
        draw_empty();
    else
        draw_centered_text(board.get_minion(position_).name, MINION_TEXT_HEIGHT_RATIO, true);
}
