#include "gui/HeroPowerElement.h"

#include "gui/GameGui.h"

HeroPowerElement::HeroPowerElement(
    const GameGui& gui, float x, float y, float width, float height, bool is_player_side
): GuiElement(gui, x, y, width, height, is_player_side)
{}

GuiElementId HeroPowerElement::id() const
{
    return std::make_pair(GuiElementIdType::HERO_POWER, is_player_side_);
}

static const float HERO_POWER_TEXT_HEIGHT_RATIO = 0.25f;

void HeroPowerElement::draw_(const Game& game) const
{
    const auto& hero = to_draw(game).hero;

    auto hero_power_rect = scaled_rect();
    unsigned text_height = scaled_height(HERO_POWER_TEXT_HEIGHT_RATIO);

    draw_centered_text(hero->hero_power_name, text_height);

    const raylib::Vector2 stat_rect_size(
        hero_power_rect.width / STAT_BOX_SIZE_RATIO,
        hero_power_rect.height * SMALL_STAT_BOX_HEIGHT_MULTIPLIER / STAT_BOX_SIZE_RATIO
    );

    const raylib::Rectangle mana_rect(
        {hero_power_rect.x + hero_power_rect.width - stat_rect_size.x, hero_power_rect.y}, stat_rect_size
    );

    mana_rect.Draw(MANA_COLOUR);
    draw_text(std::to_string(hero->hero_power_mana_cost), text_height, mana_rect);
}