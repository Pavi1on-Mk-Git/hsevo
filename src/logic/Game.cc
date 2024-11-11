#include "logic/Game.h"

#include <algorithm>
#include <ranges>
#include <spdlog/spdlog.h>

#include "logic/cards/Coin.h"
#include "utils/Rng.h"

Game::Game(const Decklist& first_decklist, const Decklist& second_decklist, bool reverse_player_order):
    players_({first_decklist, second_decklist}), active_player_(reverse_player_order ? 1 : 0), turn_ended(false)
{
    mulligan();
}

std::optional<GameResult> Game::check_winner() const
{
    using enum GameResult;

    bool first_player_dead = players_.at(0).hero->health <= 0;
    bool second_player_dead = players_.at(1).hero->health <= 0;

    if(first_player_dead && second_player_dead)
        return TIE;
    else if(first_player_dead)
        return PLAYER_2;
    else if(second_player_dead)
        return PLAYER_1;
    else
        return std::nullopt;
}

void Game::switch_active_player()
{
    active_player_ = 1 - active_player_;
}

Player& Game::current_player()
{
    return players_.at(active_player_);
}

Player& Game::opponent()
{
    return players_.at(1 - active_player_);
}

const Player& Game::current_player() const
{
    return players_.at(active_player_);
}

const Player& Game::opponent() const
{
    return players_.at(1 - active_player_);
}

static const unsigned FIRST_DRAW_AMOUNT = 3;

void Game::mulligan()
{
    draw(FIRST_DRAW_AMOUNT);
    switch_active_player();

    draw(FIRST_DRAW_AMOUNT + 1);
    current_player().hand.add_cards(&Coin::instance);
    switch_active_player();
}

void Game::draw(unsigned amount)
{
    auto [drawn_cards, fatigue_count] = current_player().deck.draw(amount);
    current_player().hand.add_cards(std::move(drawn_cards));
    current_player().hero->fatigue(fatigue_count);
}

void Game::draw()
{
    auto drawn_card = current_player().deck.draw();
    if(drawn_card)
        current_player().hand.add_cards(std::move(drawn_card));
    else
        current_player().hero->fatigue(1);
}

std::vector<std::unique_ptr<Action>> Game::get_possible_actions() const
{
    std::vector<std::unique_ptr<Action>> possible_actions;
    for(auto [hand_position, current_card]: std::views::enumerate(current_player().hand))
    {
        auto play_card_actions = current_card->create_play_actions(*this, hand_position);
        std::ranges::move(play_card_actions, std::back_inserter(possible_actions));
    }

    auto attack_actions = get_attack_actions();
    std::ranges::move(attack_actions, std::back_inserter(possible_actions));

    auto& current_hero = current_player().hero;

    if(current_hero->hero_power_active && current_player().mana >= current_hero->hero_power_mana_cost)
    {
        auto hero_power_actions = current_player().hero->create_hero_power_use_actions(*this);
        std::ranges::move(hero_power_actions, std::back_inserter(possible_actions));
    }

    possible_actions.push_back(std::make_unique<EndTurnAction>());

    return possible_actions;
}

std::vector<std::unique_ptr<Action>> Game::get_attack_actions() const
{
    std::vector<std::unique_ptr<Action>> attack_actions;

    std::vector<unsigned> taunt_minion_positions;

    for(auto [opponent_board_position, opponent_minion]: std::views::enumerate(opponent().board))
        if(opponent_minion.keywords & TAUNT)
            taunt_minion_positions.push_back(opponent_board_position);

    for(auto [current_board_position, current_minion]: std::views::enumerate(current_player().board))
    {
        if(!current_minion.active || (current_minion.keywords & CANT_ATTACK))
            continue;

        if(taunt_minion_positions.empty())
        {
            attack_actions.push_back(std::make_unique<HitHeroAction>(current_board_position));

            for(unsigned opponent_board_position = 0; opponent_board_position < opponent().board.minion_count();
                ++opponent_board_position)
                attack_actions.push_back(std::make_unique<TradeAction>(current_board_position, opponent_board_position)
                );
        }
        else
            for(unsigned taunt_minion_position: taunt_minion_positions)
                attack_actions.push_back(std::make_unique<TradeAction>(current_board_position, taunt_minion_position));
    }

    if(current_player().hero->active && current_player().hero->weapon)
    {
        if(taunt_minion_positions.empty())
        {
            attack_actions.push_back(std::make_unique<HeroHitHeroAction>());

            for(unsigned opponent_board_position = 0; opponent_board_position < opponent().board.minion_count();
                ++opponent_board_position)
                attack_actions.push_back(std::make_unique<HeroTradeAction>(opponent_board_position));
        }
        else
            for(unsigned taunt_minion_position: taunt_minion_positions)
                attack_actions.push_back(std::make_unique<HeroTradeAction>(taunt_minion_position));
    }

    return attack_actions;
}

HeroInput Game::get_hero_state(unsigned player_index) const
{
    const auto& player = players_.at(player_index);
    const auto& hero = player.hero;

    auto hero_hero = player.hero->weapon ?
                         HeroStateInput{hero->health, hero->active, hero->weapon->attack, hero->weapon->durability} :
                         HeroStateInput{hero->health, false, 0, 0};

    std::array<MinionStateInput, Board::MAX_BOARD_SIZE> minion_heros;

    for(auto [curr_minion, minion_hero]: std::views::zip(player.board, minion_heros))
    {
        minion_hero = MinionStateInput{
            curr_minion.health, curr_minion.attack, curr_minion.active && !(curr_minion.keywords & CANT_ATTACK),
            static_cast<bool>(curr_minion.keywords & TAUNT)
        };
    }

    const unsigned board_size = player.board.minion_count();

    for(auto& minion_hero: minion_heros | std::views::drop(board_size))
        minion_hero = MinionStateInput{};

    return HeroInput{hero_hero, minion_heros, player.hand.size(), board_size, player.mana};
}

GameStateInput Game::get_state() const
{
    return GameStateInput{{get_hero_state(active_player_), get_hero_state(1 - active_player_)}};
}

std::vector<Game> Game::do_action(const EndTurnAction&)
{
    turn_ended = true;

    SPDLOG_INFO("Player has ended their turn");

    current_player().board.trigger_end_of_turn();
    opponent().board.trigger_end_of_turn();
    current_player().board.remove_dead_minions();
    opponent().board.remove_dead_minions();

    return {*this};
}

std::vector<Game> Game::do_action(const PlayMinionAction& action)
{
    current_player().mana -= action.card_cost;

    const auto* played_card = static_cast<const MinionCard*>(current_player().hand.remove_card(action.hand_position));
    current_player().board.add_minion(Minion(*played_card), action.board_position);

    auto new_states = played_card->on_play(*this, action.args);

    SPDLOG_INFO(
        "Player has played {} from hand position {} for {} mana in board position {}", played_card->name,
        action.hand_position, action.card_cost, action.board_position
    );

    std::ranges::for_each(new_states, [](Game& game) {
        game.current_player().board.remove_dead_minions();
        game.opponent().board.remove_dead_minions();
    });

    return new_states;
}

std::vector<Game> Game::do_action(const PlaySpellAction& action)
{
    current_player().mana -= action.card_cost;

    auto played_card = current_player().hand.remove_card(action.hand_position);

    auto new_states = played_card->on_play(*this, action.args);

    SPDLOG_INFO(
        "Player has played {} from hand position {} for {} mana", played_card->name, action.hand_position,
        action.card_cost
    );

    std::ranges::for_each(new_states, [](Game& game) {
        game.current_player().board.remove_dead_minions();
        game.opponent().board.remove_dead_minions();
    });

    return new_states;
}

std::vector<Game> Game::do_action(const TradeAction& action)
{
    auto& first_minion = current_player().board.get_minion(action.first_target);
    auto& second_minion = opponent().board.get_minion(action.second_target);

    first_minion.health -= second_minion.attack;
    second_minion.health -= first_minion.attack;

    first_minion.active = false;

    SPDLOG_INFO(
        "Player has traded {} from position {} into {} in position {}", first_minion.name, action.first_target,
        second_minion.name, action.second_target
    );

    current_player().board.remove_dead_minions();
    opponent().board.remove_dead_minions();

    return {*this};
}

std::vector<Game> Game::do_action(const HitHeroAction& action)
{
    auto& minion = current_player().board.get_minion(action.position);

    opponent().hero->health -= minion.attack;
    minion.active = false;

    SPDLOG_INFO("Player has attacked the opponent using {} from position {}", minion.name, action.position);

    return {*this};
}

std::vector<Game> Game::do_action(const HeroPowerAction& action)
{
    current_player().mana -= current_player().hero->hero_power_mana_cost;
    current_player().hero->hero_power_active = false;

    current_player().hero->on_hero_power_use(*this, action.args);

    SPDLOG_INFO("Player has used their hero power");

    current_player().board.remove_dead_minions();
    opponent().board.remove_dead_minions();

    return {*this};
}

std::vector<Game> Game::do_action(const HeroTradeAction& action)
{
    auto& target_minion = opponent().board.get_minion(action.position);

    target_minion.health -= current_player().hero->weapon->attack;
    current_player().hero->health -= target_minion.attack;

    if(--current_player().hero->weapon->durability == 0)
        current_player().hero->weapon = std::nullopt;

    current_player().hero->active = false;

    SPDLOG_INFO("Player has attacked {} in position {}", target_minion.name, action.position);

    opponent().board.remove_dead_minions();

    return {*this};
}

std::vector<Game> Game::do_action(const HeroHitHeroAction&)
{
    opponent().hero->health -= current_player().hero->weapon->attack;

    if(--current_player().hero->weapon->durability == 0)
        current_player().hero->weapon = std::nullopt;

    current_player().hero->active = false;

    SPDLOG_INFO("Player has attacked their opponent");

    return {*this};
}
