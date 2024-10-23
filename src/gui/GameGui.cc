#include "gui/GameGui.h"

#include <ranges>
#include <raylib.h>
#include <tuple>

#include "ai/Network.hpp"
#include "gui/GuiPlayerLogic.h"
#include "players/EvoPlayerLogic.hpp"
#include "utils/Rng.h"

raylib::Rectangle GameGui::scale(const raylib::Rectangle& original, bool reflect)
{
    raylib::Rectangle scaled = original;
    if(reflect)
        scaled.y = 1.f - original.y - original.height;

    const auto [width_scale, height_scale] = window_.GetSize();

    scaled.x *= width_scale;
    scaled.y *= height_scale;
    scaled.width *= width_scale;
    scaled.height *= height_scale;

    return scaled;
}

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

const std::vector<std::tuple<raylib::Rectangle, GuiElementIdType, unsigned>> area_to_element = {
    {
        {0.f, 0.f, 0.25f, 0.4f},
        GuiElementIdType::HERO,
        1,
    },
    {
        {0.125f, 0.4f, 0.125f, 0.1f},
        GuiElementIdType::HERO_POWER,
        1,
    },
    {
        {0.25f, 0.f, 0.65f, 0.25f},
        GuiElementIdType::CARD,
        Board::MAX_BOARD_SIZE,
    },
    {
        {0.25f, 0.25f, 0.65f, 0.25f},
        GuiElementIdType::MINION,
        Hand::MAX_HAND_SIZE,
    },
    {
        {0.8f, 0.45f, 0.2f, 0.05f},
        GuiElementIdType::EOT_BUTTON,
        1,
    },
};

std::optional<GuiElementId> GameGui::mouse_position()
{
    const auto position = GetMousePosition();

    std::optional<GuiElementIdType> element_type;
    bool player_side = false;
    std::optional<unsigned> element_id;

    auto get_type_and_id = [&](const raylib::Rectangle& scaled, const GuiElementIdType& element, unsigned count) {
        element_type = element;
        element_id = std::floor(count * (position.x - scaled.x) / scaled.width);
    };

    auto check_areas = [&] {
        for(const auto& [area, element, count]: area_to_element)
        {
            auto scaled = scale(area, player_side);
            if(scaled.CheckCollision(position))
            {
                get_type_and_id(scaled, element, count);
                break;
            }
        }
    };

    check_areas();

    if(!element_type)
    {
        player_side = true;
        check_areas();
    }

    if(!element_type)
        return std::nullopt;

    using enum GuiElementIdType;
    switch(*element_type)
    {
    case HERO:
    case HERO_POWER:
        return std::make_pair(*element_type, player_side);
    case CARD:
    case MINION:
        return std::make_tuple(*element_type, player_side, *element_id);
    default:
        return *element_type;
    }
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

        if((gui_elements.size() < clicked_elements.size()) ||
           !std::ranges::all_of(std::views::zip(gui_elements, clicked_elements), [](const auto& expected_and_clicked) {
               return expected_and_clicked.first == expected_and_clicked.second;
           }))
            element_sequences.emplace_back();
        else
            element_sequences.emplace_back(gui_elements.begin() + clicked_elements.size(), gui_elements.end());
    }

    return element_sequences;
}