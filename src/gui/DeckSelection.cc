#include "gui/DeckSelection.h"

#include <algorithm>
#include <ranges>

DeckSelection::DeckSelection(
    raylib::Window& window, const std::vector<const Decklist*>& decklists,
    const std::vector<std::ifstream*>& logic_files
): window_(window), decklists_(decklists), logic_files_(logic_files), player_deck_(nullptr), bot_deck_(nullptr)
{
    const unsigned deck_choice_button_height = window.GetHeight() / (decklists_.size() + 1);
    const unsigned deck_choice_button_width = window.GetWidth();
    unsigned offset = deck_choice_button_height;

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
    const unsigned deck_choice_button_height = window_.GetHeight() / (decklists_.size() + 1);
    const unsigned deck_choice_button_width = window_.GetWidth();
    unsigned offset = deck_choice_button_height;

    for(auto& deck_choice_button: deck_choice_buttons_)
    {
        deck_choice_button = raylib::Rectangle(0, offset, deck_choice_button_width, deck_choice_button_height);
        offset += deck_choice_button_height;
    }

    const raylib::Vector2 mouse_position = GetMousePosition();
    for(auto [decklist, logic_file, button, is_highlighted]:
        std::views::zip(decklists_, logic_files_, deck_choice_buttons_, button_is_highlighted))
    {
        if(!(is_highlighted = button.CheckCollision(mouse_position)))
            continue;

        if(!IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            continue;

        if(!player_deck_)
        {
            player_deck_ = decklist;
            break;
        }
        else if(!bot_deck_)
        {
            bot_deck_ = decklist;
            bot_logic_file_ = logic_file;
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
const unsigned TEXT_HEIGHT_DIVISOR = 3;
const unsigned TEXT_SPACING_DIVISOR = 10;

void DeckSelection::draw()
{
    window_.BeginDrawing();
    window_.ClearBackground(DECK_SELECTION_BG_COLOUR);

    const raylib::Rectangle info_rect(0, 0, window_.GetWidth(), window_.GetHeight() / (decklists_.size() + 1));
    info_rect.DrawLines(DECK_CHOICE_BUTTON_COLOUR, DECK_CHOICE_BUTTON_BORDER_THICKNESS);

    const unsigned text_height = info_rect.height / TEXT_HEIGHT_DIVISOR;
    const unsigned text_spacing = text_height / TEXT_SPACING_DIVISOR;

    if(!player_deck_)
    {
        const raylib::Text text(
            "Select the player deck", text_height, DECK_CHOICE_BUTTON_COLOUR, GetFontDefault(), text_spacing
        );
        const unsigned text_width = text.Measure();
        const raylib::Vector2 offset{(info_rect.width - text_width) / 2, (info_rect.height - text_height) / 2};
        text.Draw(offset);
    }
    else if(!bot_deck_)
    {
        const raylib::Text text(
            "Select the bot deck", text_height, DECK_CHOICE_BUTTON_COLOUR, GetFontDefault(), text_spacing
        );
        const unsigned text_width = text.Measure();
        const raylib::Vector2 offset{(info_rect.width - text_width) / 2, (info_rect.height - text_height) / 2};
        text.Draw(offset);
    }

    for(auto [decklist_id, decklist, deck_button, is_highlighted]:
        std::views::zip(std::views::iota(1), decklists_, deck_choice_buttons_, button_is_highlighted))
    {
        if(is_highlighted)
            deck_button.Draw(HIGHLIGHT_COLOR);

        deck_button.DrawLines(DECK_CHOICE_BUTTON_COLOUR, DECK_CHOICE_BUTTON_BORDER_THICKNESS);

        const unsigned text_height = deck_button.GetHeight() / TEXT_HEIGHT_DIVISOR;
        const unsigned text_spacing = text_height / TEXT_SPACING_DIVISOR;

        const raylib::Text text(decklist->name, text_height, DECK_CHOICE_BUTTON_COLOUR, GetFontDefault(), text_spacing);

        const unsigned text_width = text.Measure();

        const raylib::Vector2 offset{
            (deck_button.GetWidth() - text_width) / 2,
            deck_button.GetHeight() * decklist_id + (deck_button.GetHeight() - text_height) / 2
        };

        text.Draw(offset);
    }
    window_.EndDrawing();
}

std::tuple<const Decklist*, const Decklist*, std::ifstream*> DeckSelection::run()
{
    while(!window_.ShouldClose() && !(player_deck_ && bot_deck_))
    {
        update();
        draw();
    }
    if(!window_.ShouldClose())
        return {player_deck_, bot_deck_, bot_logic_file_};
    else
        return {nullptr, nullptr, nullptr};
}