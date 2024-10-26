#include "gui/GameGui.h"

#include <ranges>
#include <raylib.h>
#include <tuple>

#include "ai/Network.hpp"
#include "gui/CardElement.h"
#include "gui/GuiPlayerLogic.h"
#include "gui/HeroElement.h"
#include "gui/HeroPowerElement.h"
#include "gui/WeaponElement.h"
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

    auto& logic = is_player_turn() ? player_logic_ : bot_logic_;

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

bool GameGui::is_player_turn() const
{
    return current_turn_ % 2 != is_bot_first_;
}

raylib::Rectangle GameGui::scale(const raylib::Rectangle& original) const
{
    raylib::Rectangle scaled = original;

    const auto [width_scale, height_scale] = window_.GetSize();

    scaled.x *= width_scale;
    scaled.y *= height_scale;
    scaled.width *= width_scale;
    scaled.height *= height_scale;

    return scaled;
}

std::optional<GuiElementId> GameGui::clicked_element() const
{
    const auto position = GetMousePosition();

    for(const auto& element: elements_)
        if(scale(element->base_area).CheckCollision(position))
            return element->id();
    return std::nullopt;
}

void GameGui::draw()
{
    window_.BeginDrawing();

    for(const auto& element: elements_)
        element->draw(game_);

    window_.EndDrawing();
}

const float HERO_WIDTH = 0.2f, HERO_HEIGHT = 0.4f, HERO_POWER_LEN = 0.1f, ENTITY_HEIGHT = 0.25f,
            ALL_ENTITIES_WIDTH = 0.6f, CARD_WIDTH = ALL_ENTITIES_WIDTH / Hand::MAX_HAND_SIZE,
            MINION_WIDTH = ALL_ENTITIES_WIDTH / Board::MAX_BOARD_SIZE, EOT_HEIGHT = 0.1f,
            EOT_WIDTH = 1 - HERO_WIDTH - ALL_ENTITIES_WIDTH;

GameGui::GameGui(raylib::Window& window, const Decklist* player_deck, const Decklist* bot_deck, std::istream& in):
    window_(window), is_bot_first_(Rng::instance().uniform_int(0, 1)), is_turn_started_(false),
    player_logic_(new GuiPlayerLogic(*player_deck, *this)), bot_logic_(new EvoPlayerLogic<Network>(*bot_deck, in)),
    game_(*player_deck, *bot_deck, is_bot_first_), winner_(game_.check_winner()), current_turn_(0)
{
    for(bool is_player_side: {false, true})
    {
        elements_.push_back(std::make_unique<HeroElement>(*this, 0.f, 0.f, HERO_WIDTH, HERO_HEIGHT, is_player_side));
        elements_.push_back(std::make_unique<HeroPowerElement>(
            *this, HERO_POWER_LEN, HERO_HEIGHT, HERO_POWER_LEN, HERO_POWER_LEN, is_player_side
        ));
        elements_.push_back(
            std::make_unique<WeaponElement>(*this, 0.f, HERO_HEIGHT, HERO_POWER_LEN, HERO_POWER_LEN, is_player_side)
        );

        for(unsigned hand_id = 0; hand_id < Hand::MAX_HAND_SIZE; ++hand_id)
            elements_.push_back(std::make_unique<CardElement>(
                *this, HERO_WIDTH + CARD_WIDTH * hand_id, 0.f, CARD_WIDTH, ENTITY_HEIGHT, is_player_side, hand_id
            ));
    }
}

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
