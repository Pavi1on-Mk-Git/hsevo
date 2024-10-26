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

void HeroPowerElement::draw(const Game& game) const
{
    const auto& hero = gui_.is_player_turn() ? game.current_player().hero : game.opponent().hero;

    draw_centered_text(hero->hero_power_name, HERO_POWER_TEXT_HEIGHT_RATIO);
}