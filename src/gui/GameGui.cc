#include "gui/GameGui.h"

#include <raylib.h>
#include <tuple>

#include "ai/Network.hpp"
#include "gui/GuiPlayerLogic.h"
#include "players/EvoPlayerLogic.hpp"
#include "utils/Rng.h"

void GameGui::update()
{
    if(!is_turn_started_)
    {
        ++current_turn_;
        update_begin_turn();

        if((winner_ = game_.check_winner()))
            return;
    }

    auto& logic = (current_turn_ % 2 == is_bot_first_) ? bot_logic_ : player_logic_;

    game_ = logic->choose_and_apply_action(game_, game_.get_possible_actions());

    if(game_.turn_ended)
    {
        game_.switch_active_player();
        is_turn_started_ = false;
    }
}

void GameGui::update_begin_turn()
{
    game_.draw();

    if((winner_ = game_.check_winner()))
        return;

    auto& current_mana_crystals = game_.current_player().mana_crystals;

    if(current_mana_crystals < Player::MAX_MANA)
        current_mana_crystals++;

    game_.current_player().mana = current_mana_crystals;
    game_.current_player().hero->hero_power_active = true;
    game_.current_player().hero->active = true;

    for(unsigned minion_index = 0; minion_index < game_.current_player().board.minion_count(); ++minion_index)
        game_.current_player().board.get_minion(minion_index).active = true;

    game_.turn_ended = false;

    is_turn_started_ = true;
}

GuiElementId GameGui::mouse_position()
{
    return GuiElementIdType::EOT_BUTTON;
}

void GameGui::draw()
{
    window_.BeginDrawing();

    window_.ClearBackground(RAYWHITE);

    raylib::Text text("Game Gui is being drawn", 40.f, BLACK, GetFontDefault(), 1.f);

    auto [width, height] = window_.GetSize();
    auto [x, y] = text.MeasureEx();
    text.Draw((width - x) / 2, (height - y) / 2);

    window_.EndDrawing();
}

GameGui::GameGui(raylib::Window& window, const Decklist* player_deck, const Decklist* bot_deck, std::istream& in):
    window_(window), is_bot_first_(Rng::instance().uniform_int(0, 1)), is_turn_started_(false),
    player_logic_(new GuiPlayerLogic(*player_deck, *this)), bot_logic_(new EvoPlayerLogic<Network>(*bot_deck, in)),
    game_(*player_deck, *bot_deck, is_bot_first_), winner_(game_.check_winner()), current_turn_(0)
{}

GameResult GameGui::run()
{
    while(!window_.ShouldClose() && !winner_)
    {
        update();
        draw();
    }

    if(!window_.ShouldClose())
        return *winner_;
    else
        return GameResult::TIE;
}

std::vector<std::deque<GuiElementId>> GameGui::actions_to_elements(
    const std::vector<std::unique_ptr<Action>>& actions, const std::deque<GuiElementId>& clicked_elements
)
{
    std::vector<std::deque<GuiElementId>> element_sequences;

    for(const auto& action: actions)
    {
        std::deque<GuiElementId> gui_elements = action->element_sequence();
        bool is_prefix = true;
        for(const auto& element: clicked_elements)
        {
            if(gui_elements.front() == element)
                gui_elements.pop_front();
            else
            {
                is_prefix = false;
                break;
            }
        }
        if(is_prefix)
            element_sequences.push_back(gui_elements);
    }

    return element_sequences;
}