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
static const raylib::Color SECRET_COLOUR = LIGHTGRAY;
static const raylib::Color ARMOUR_COLOUR = LIGHTGRAY;

void HeroElement::draw_(const Game& game) const
{
    const auto& player = to_draw(game);
    const auto& hero = player.hero;

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

    if(hero->armour > 0)
    {
        const raylib::Rectangle armour_rect({right_aligned_x, down_aligned_y - stat_rect_size.y}, stat_rect_size);

        armour_rect.Draw(ARMOUR_COLOUR);
        draw_text(std::to_string(hero->armour), text_height, armour_rect);
    }

    if(!player.secrets.empty())
    {
        const raylib::Rectangle secret_rect({hero_rect.x, hero_rect.y}, stat_rect_size);

        secret_rect.Draw(SECRET_COLOUR);
        draw_text(std::to_string(player.secrets.size()), text_height, secret_rect);
    }
}