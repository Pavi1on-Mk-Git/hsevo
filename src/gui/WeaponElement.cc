#include "gui/WeaponElement.h"

#include "gui/GameGui.h"

WeaponElement::WeaponElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side):
    GuiElement(gui, x, y, width, height, is_player_side)
{}

GuiElementId WeaponElement::id() const
{
    return GuiElementIdType::OTHER;
}

static const float WEAPON_TEXT_HEIGHT_RATIO = 0.25f;
static const raylib::Color WEAPON_STAT_COLOUR = LIGHTGRAY;

void WeaponElement::draw_(const Game& game) const
{
    const auto& weapon = to_draw(game).hero->weapon;

    if(weapon)
    {
        const auto weapon_rect = scaled_rect();
        const float text_height = scaled_height(WEAPON_TEXT_HEIGHT_RATIO);

        draw_centered_text(weapon->name, text_height, true);

        const raylib::Vector2 stat_rect_size(
            weapon_rect.width / STAT_BOX_SIZE_RATIO,
            weapon_rect.height * SMALL_STAT_BOX_HEIGHT_MULTIPLIER / STAT_BOX_SIZE_RATIO
        );

        const float right_aligned_x = weapon_rect.x + weapon_rect.width - stat_rect_size.x,
                    down_aligned_y = weapon_rect.y + weapon_rect.height - stat_rect_size.y;


        const raylib::Rectangle attack_rect({weapon_rect.x, down_aligned_y}, stat_rect_size);

        attack_rect.Draw(WEAPON_STAT_COLOUR);
        draw_text(std::to_string(weapon->attack), text_height, attack_rect);

        const raylib::Rectangle health_rect({right_aligned_x, down_aligned_y}, stat_rect_size);

        health_rect.Draw(WEAPON_STAT_COLOUR);
        draw_text(std::to_string(weapon->durability), text_height, health_rect);
    }
    else
        draw_empty();
}