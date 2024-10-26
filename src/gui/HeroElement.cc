#include "gui/HeroElement.h"

#include "gui/GameGui.h"
#include "gui/utils.h"

HeroElement::HeroElement(const GameGui& gui, float x, float y, float width, float height, bool is_player_side):
    GuiElement(gui, x, y, width, height, is_player_side)
{}

GuiElementId HeroElement::id() const
{
    return std::make_pair(GuiElementIdType::HERO, is_player_side_);
}

static const raylib::Color HERO_BG_COLOUR = BEIGE;
static const unsigned HERO_TEXT_SIZE = 30;

void HeroElement::draw(const Game& game) const
{
    auto scaled = gui_.scale(base_area);

    const auto& hero = gui_.is_player_turn() ? game.current_player().hero : game.opponent().hero;

    raylib::Text hero_text(hero->name, HERO_TEXT_SIZE, TEXT_COLOUR, GetFontDefault(), HERO_TEXT_SIZE / SPACING_DIVISOR);

    scaled.Draw(HERO_BG_COLOUR);

    if(is_active)
        scaled.DrawLines(ACTIVE_COLOUR, BORDER_THICKNESS);

    hero_text.Draw(
        scaled.GetPosition() +
        center_offset(scaled.GetSize(), {static_cast<float>(hero_text.Measure()), HERO_TEXT_SIZE})
    );
}