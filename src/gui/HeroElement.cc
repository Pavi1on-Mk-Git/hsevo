#include "gui/HeroElement.h"

#include "gui/GameGui.h"

HeroElement::HeroElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side):
    GuiElement(gui, x, y, width, height, is_player_side)
{}

GuiElementId HeroElement::id() const
{
    return std::make_pair(GuiElementIdType::HERO, is_player_side_);
}

static const float HERO_TEXT_HEIGHT_RATIO = 0.15f;

void HeroElement::draw_(const Game& game) const
{
    const auto& hero = to_draw(game).hero;

    auto hero_rect = scaled_rect();
    const float text_height = scaled_height(HERO_TEXT_HEIGHT_RATIO);

    draw_centered_text(hero->name, text_height, true);

    const raylib::Vector2 stat_rect_size(
        hero_rect.width / STAT_BOX_WIDTH_RATIO, hero_rect.height / STAT_BOX_HEIGHT_RATIO
    );

    const float right_aligned_x = hero_rect.x + hero_rect.width - stat_rect_size.x,
                down_aligned_y = hero_rect.y + hero_rect.height - stat_rect_size.y;

    if(hero->weapon && (gui_.is_player_turn() == is_player_side_))
    {
        const raylib::Rectangle attack_rect({hero_rect.x, down_aligned_y}, stat_rect_size);

        attack_rect.Draw(ATTACK_COLOUR);
        draw_text(std::to_string(hero->weapon->attack), text_height, attack_rect);
    }

    const raylib::Rectangle health_rect({right_aligned_x, down_aligned_y}, stat_rect_size);

    health_rect.Draw(HEALTH_COLOUR);
    draw_text(std::to_string(hero->health), text_height, health_rect);
}