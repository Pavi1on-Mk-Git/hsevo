#include "gui/DeckSelection.h"

#include <algorithm>

DeckSelection::DeckSelection(raylib::Window& window, const std::vector<const Decklist*>& decklists):
    window_(window), decklists_(decklists), player_deck_(nullptr), bot_deck_(nullptr)
{
    const unsigned deck_choice_button_height = window.GetHeight() / decklists_.size();
    const unsigned deck_choice_button_width = window.GetWidth();
    unsigned offset = 0;

    deck_choice_buttons_.reserve(decklists_.size());
    for(unsigned i = 0; i < decklists_.size(); ++i)
    {
        deck_choice_buttons_.emplace_back(0, offset, deck_choice_button_width, deck_choice_button_height);
        offset += deck_choice_button_height;
    }

    button_is_highlighted.resize(decklists_.size());
}

void DeckSelection::update()
{
    const raylib::Vector2 mouse_position = GetMousePosition();
    for(unsigned decklist_id = 0; decklist_id < decklists_.size(); ++decklist_id)
    {
        if(!(button_is_highlighted.at(decklist_id) = deck_choice_buttons_.at(decklist_id).CheckCollision(mouse_position)
           ))
            continue;

        if(!IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            continue;

        if(!player_deck_)
        {
            player_deck_ = decklists_.at(decklist_id);
            break;
        }
        else if(!bot_deck_)
        {
            bot_deck_ = decklists_.at(decklist_id);
            break;
        }
        else
            break;
    }
}

const raylib::Color DECK_SELECTION_BG_COLOUR = WHITE;
const raylib::Color DECK_CHOICE_BUTTON_COLOUR = BLACK;
const raylib::Color HIGHLIGHT_COLOR(0, 158, 47, 128);
const float DECK_CHOICE_BUTTON_BORDER_THICKNESS = 5.f;
const unsigned TEXT_HEIGHT_DIVISOR = 2;
const unsigned TEXT_SPACING_DIVISOR = 10;

void DeckSelection::draw()
{
    window_.BeginDrawing();
    window_.ClearBackground(DECK_SELECTION_BG_COLOUR);
    for(unsigned decklist_id = 0; decklist_id < decklists_.size(); ++decklist_id)
    {
        const raylib::Rectangle& deck_button = deck_choice_buttons_.at(decklist_id);

        if(button_is_highlighted.at(decklist_id))
            deck_button.Draw(HIGHLIGHT_COLOR);

        deck_button.DrawLines(DECK_CHOICE_BUTTON_COLOUR, DECK_CHOICE_BUTTON_BORDER_THICKNESS);

        const unsigned text_height = deck_button.GetHeight() / TEXT_HEIGHT_DIVISOR;
        const unsigned text_spacing = text_height / TEXT_SPACING_DIVISOR;

        const raylib::Text text(
            decklists_.at(decklist_id)->name, text_height, DECK_CHOICE_BUTTON_COLOUR, GetFontDefault(), text_spacing
        );

        const unsigned text_width = text.Measure();

        const raylib::Vector2 offset{
            (deck_button.GetWidth() - text_width) / 2,
            deck_button.GetHeight() * decklist_id + (deck_button.GetHeight() - text_height) / 2
        };

        text.Draw(offset);
    }
    window_.EndDrawing();
}

std::pair<const Decklist*, const Decklist*> DeckSelection::run()
{
    while(!window_.ShouldClose() && !(player_deck_ && bot_deck_))
    {
        update();
        draw();
    }
    if(!window_.ShouldClose())
        return {player_deck_, bot_deck_};
    else
        return {nullptr, nullptr};
}