#include "gui/PostGameScreen.h"

PostGameScreen::PostGameScreen(raylib::Window& window, const BotGameResult& result): window_(window)
{
    switch(result)
    {
    case BotGameResult::PLAYER:
        text_ = "Congratulations, you won!!!";
        break;
    case BotGameResult::BOT:
        text_ = "You'll get 'em next time";
        break;
    case BotGameResult::TIE:
        text_ = "It's a tie";
        break;
    }
}

const raylib::Color POST_GAME_BG_COLOUR = WHITE;
const raylib::Color POST_GAME_TEXT_COLOUR = BLACK;
const unsigned TEXT_HEIGHT_DIVISOR = 15;
const unsigned TEXT_SPACING_DIVISOR = 10;

void PostGameScreen::draw() const
{
    window_.BeginDrawing();
    window_.ClearBackground(POST_GAME_BG_COLOUR);

    const unsigned text_height = window_.GetHeight() / TEXT_HEIGHT_DIVISOR;
    const unsigned text_spacing = text_height / TEXT_SPACING_DIVISOR;

    const raylib::Text text(text_, text_height, POST_GAME_TEXT_COLOUR, GetFontDefault(), text_spacing);
    const unsigned text_width = text.Measure();
    text.Draw((window_.GetWidth() - text_width) / 2, (window_.GetHeight() - text_height) / 2);

    window_.EndDrawing();
}

void PostGameScreen::run() const
{
    while(!window_.ShouldClose())
        draw();
}
