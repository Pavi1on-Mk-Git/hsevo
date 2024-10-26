#include "gui/HeroElement.h"

#include "gui/GameGui.h"

HeroElement::HeroElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side):
    GuiElement(gui, x, y, width, height, is_player_side)
{}

GuiElementId HeroElement::id() const
{
    return std::make_pair(GuiElementIdType::HERO, is_player_side_);
}

static const float HERO_TEXT_HEIGHT_RATIO = 0.2f;

void HeroElement::draw(const Game& game) const
{
    const auto& hero = gui_.is_player_turn() ? game.current_player().hero : game.opponent().hero;

    draw_centered_text(hero->name, HERO_TEXT_HEIGHT_RATIO);
}