#include "gui/GameGui.h"

#include <algorithm>
#include <chrono>
#include <ranges>
#include <thread>
#include <tuple>

#include "ai/Network.hpp"
#include "gui/CardElement.h"
#include "gui/DeckElement.h"
#include "gui/EOTElement.h"
#include "gui/GuiPlayerLogic.h"
#include "gui/HeroElement.h"
#include "gui/HeroPowerElement.h"
#include "gui/MinionElement.h"
#include "gui/WeaponElement.h"
#include "players/EvoPlayerLogic.hpp"
#include "utils/Rng.h"

const unsigned BOT_SLEEP_TIME_MILLIS = 1000;

Game GameGui::delayed_action()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(BOT_SLEEP_TIME_MILLIS));
    return bot_logic_->choose_and_apply_action(game_, game_.get_possible_actions());
}

void GameGui::update()
{
    if(!is_turn_started_)
    {
        update_begin_turn();

        if((winner_ = game_.check_winner()))
            return;
    }

    if(is_player_turn())
        game_ = player_logic_->choose_and_apply_action(game_, game_.get_possible_actions());
    else
    {
        if(!bot_action_result_.valid())
            bot_action_result_ = std::async(std::launch::async, &GameGui::delayed_action, this);
        else if(bot_action_result_.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
            game_ = bot_action_result_.get();
    }

    if((winner_ = game_.check_winner()))
        return;

    if(game_.turn_ended)
    {
        game_.switch_active_player();
        ++current_turn_;
        if(!is_player_turn())
            make_active();
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

    for(auto& minion: game_.current_player().board)
        minion.active = true;

    game_.turn_ended = false;

    is_turn_started_ = true;
}

bool GameGui::is_player_turn() const
{
    return (current_turn_ % 2 == 1) != is_bot_first_;
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

void GameGui::make_active(const std::vector<std::deque<GuiElementId>> potential_sequences)
{
    for(const auto& element: elements_)
        element->is_active = false;

    for(const auto& sequence: potential_sequences)
    {
        if(sequence.empty())
            continue;

        auto matching_element = std::ranges::find_if(elements_, [&sequence](const auto& element) {
            return element->id() == sequence.front();
        });

        if(matching_element != elements_.end())
            (*matching_element)->is_active = true;
    }
}

void GameGui::draw()
{
    window_.BeginDrawing();

    for(const auto& element: elements_)
        element->draw(game_);

    window_.EndDrawing();
}

const float HERO_WIDTH = 0.15f, HERO_HEIGHT = 0.3f, HERO_POWER_WIDTH = HERO_WIDTH / 2.f, ENTITY_HEIGHT = 0.25f,
            HERO_POWER_HEIGHT = 0.5f - HERO_HEIGHT, ALL_ENTITIES_WIDTH = 0.7f,
            CARD_WIDTH = ALL_ENTITIES_WIDTH / Hand::MAX_HAND_SIZE,
            MINION_WIDTH = ALL_ENTITIES_WIDTH / Board::MAX_BOARD_SIZE, EOT_HEIGHT = 0.1f,
            EOT_WIDTH = 1 - HERO_WIDTH - ALL_ENTITIES_WIDTH, DECK_HEIGHT = (1.f - EOT_HEIGHT) / 2;

GameGui::GameGui(
    raylib::Window& window, const Decklist* player_deck, const Decklist* bot_deck, std::istream& bot_logic_file
):
    window_(window), is_bot_first_(Rng::instance().uniform_int(0, 1)), is_turn_started_(false),
    player_logic_(new GuiPlayerLogic(*player_deck, *this)),
    bot_logic_(new EvoPlayerLogic<Network>(*bot_deck, bot_logic_file)), game_(*player_deck, *bot_deck, is_bot_first_),
    winner_(game_.check_winner()), current_turn_(1)
{
    for(bool is_player_side: {false, true})
    {
        elements_.push_back(std::make_unique<HeroElement>(*this, 0.f, 0.f, HERO_WIDTH, HERO_HEIGHT, is_player_side));
        elements_.push_back(std::make_unique<HeroPowerElement>(
            *this, HERO_POWER_WIDTH, HERO_HEIGHT, HERO_POWER_WIDTH, HERO_POWER_HEIGHT, is_player_side
        ));
        elements_.push_back(std::make_unique<WeaponElement>(
            *this, 0.f, HERO_HEIGHT, HERO_POWER_WIDTH, HERO_POWER_HEIGHT, is_player_side
        ));

        for(unsigned hand_id = 0; hand_id < Hand::MAX_HAND_SIZE; ++hand_id)
            elements_.push_back(std::make_unique<CardElement>(
                *this, HERO_WIDTH + CARD_WIDTH * hand_id, 0.f, CARD_WIDTH, ENTITY_HEIGHT, is_player_side, hand_id
            ));

        for(unsigned board_id = 0; board_id < Board::MAX_BOARD_SIZE; ++board_id)
            elements_.push_back(std::make_unique<MinionElement>(
                *this, HERO_WIDTH + MINION_WIDTH * board_id, ENTITY_HEIGHT, MINION_WIDTH, ENTITY_HEIGHT, is_player_side,
                board_id
            ));

        elements_.push_back(std::make_unique<DeckElement>(
            *this, HERO_WIDTH + ALL_ENTITIES_WIDTH, 0.f, EOT_WIDTH, DECK_HEIGHT, is_player_side
        ));
    }
    elements_.push_back(
        std::make_unique<EOTElement>(*this, HERO_WIDTH + ALL_ENTITIES_WIDTH, DECK_HEIGHT, EOT_WIDTH, EOT_HEIGHT)
    );
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
