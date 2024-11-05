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

void WeaponElement::draw_(const Game& game) const
{
    const auto& weapon = to_draw(game).hero->weapon;

    if(weapon)
        draw_centered_text(weapon->name, scaled_height(WEAPON_TEXT_HEIGHT_RATIO));
    else
        draw_empty();
}