#include "logic/Game.h"

#include <algorithm>

#include "utils/Rng.h"

Game::Game(std::shared_ptr<PlayerLogic> first_player, std::shared_ptr<PlayerLogic> second_player):
    players_({first_player, second_player}), game_ended_(false), turn_ended_(false)
{}

void Game::check_winner()
{
    bool first_player_dead = players_.at(0).hero->health <= 0;
    bool second_player_dead = players_.at(1).hero->health <= 0;

    if(first_player_dead || second_player_dead)
        game_ended_ = true;
    else
        return;

    if(first_player_dead && second_player_dead)
        winner_ = GameResult::TIE;
    else if(first_player_dead)
        winner_ = GameResult::PLAYER_2;
    else if(second_player_dead)
        winner_ = GameResult::PLAYER_1;
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
    for(unsigned hand_position = 0; hand_position < current_player().hand.size(); ++hand_position)
    {
        auto& current_card = current_player().hand.get_card(hand_position);
        auto play_card_actions = current_card->create_play_actions(*this, hand_position);
        std::move(play_card_actions.begin(), play_card_actions.end(), std::back_inserter(possible_actions));
    }

    auto attack_actions = get_attack_actions();
    std::move(attack_actions.begin(), attack_actions.end(), std::back_inserter(possible_actions));

    auto& current_hero = current_player().hero;

    if(current_hero->hero_power_active && current_player().mana >= current_hero->hero_power_mana_cost)
    {
        auto hero_power_actions = current_player().hero->create_hero_power_use_actions(*this);
        std::move(hero_power_actions.begin(), hero_power_actions.end(), std::back_inserter(possible_actions));
    }

    possible_actions.push_back(std::make_unique<EndTurnAction>());

    return possible_actions;
}

std::vector<std::unique_ptr<Action>> Game::get_attack_actions() const
{
    std::vector<std::unique_ptr<Action>> attack_actions;

    std::vector<unsigned> taunt_minion_positions;

    for(unsigned opponent_board_position = 0; opponent_board_position < opponent().board.minion_count();
        ++opponent_board_position)
        if(opponent().board.get_minion(opponent_board_position).keywords & TAUNT)
            taunt_minion_positions.push_back(opponent_board_position);

    for(unsigned current_board_position = 0; current_board_position < current_player().board.minion_count();
        ++current_board_position)
    {
        auto& current_minion = current_player().board.get_minion(current_board_position);
        if(!current_minion.active || current_minion.keywords & CANT_ATTACK)
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
            for(auto taunt_minion_position: taunt_minion_positions)
                attack_actions.push_back(std::make_unique<TradeAction>(current_board_position, taunt_minion_position));
    }

    return attack_actions;
}

HeroInput Game::get_hero_state(unsigned player_index) const
{
    HeroStateInput hero_hero{static_cast<unsigned>(players_.at(player_index).hero->health)};
    std::array<MinionStateInput, Board::MAX_BOARD_SIZE> minion_heros;

    const unsigned board_size = players_.at(player_index).board.minion_count();
    for(unsigned minion_index = 0; minion_index < board_size; ++minion_index)
    {
        auto& curr_minion = players_.at(player_index).board.get_minion(minion_index);
        minion_heros.at(minion_index) = MinionStateInput{static_cast<unsigned>(curr_minion.health), curr_minion.attack};
    }
    for(unsigned empty_space_index = board_size; empty_space_index < Board::MAX_BOARD_SIZE - board_size;
        ++empty_space_index)
        minion_heros.at(empty_space_index) = MinionStateInput();

    return HeroInput{
        hero_hero, minion_heros, players_.at(player_index).hand.size(), board_size, players_.at(player_index).mana};
}

GameStateInput Game::get_state() const
{
    return GameStateInput{{get_hero_state(active_player_), get_hero_state(1 - active_player_)}};
}

std::vector<Game> Game::do_action(const EndTurnAction& action)
{
    static_cast<void>(action);

    turn_ended_ = true;

    return {*this};
}

std::vector<Game> Game::do_action(const PlayMinionAction& action)
{
    current_player().mana -= action.card_cost;

    auto* played_card = static_cast<MinionCard*>(current_player().hand.remove_card(action.hand_position).release());
    current_player().board.add_minion(Minion(*played_card), action.board_position);

    auto new_states = played_card->on_play(*this, action.args);

    std::for_each(new_states.begin(), new_states.end(), [](Game& game) {
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

    std::for_each(new_states.begin(), new_states.end(), [](Game& game) {
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

    current_player().board.remove_dead_minions();
    opponent().board.remove_dead_minions();

    return {*this};
}

std::vector<Game> Game::do_action(const HitHeroAction& action)
{
    opponent().hero->health -= current_player().board.get_minion(action.position).attack;

    return {*this};
}

std::vector<Game> Game::do_action(const HeroPowerAction& action)
{
    current_player().mana -= current_player().hero->hero_power_mana_cost;
    current_player().hero->hero_power_active = false;

    auto new_states = current_player().hero->on_hero_power_use(*this, action.args);

    std::for_each(new_states.begin(), new_states.end(), [](Game& game) {
        game.current_player().board.remove_dead_minions();
        game.opponent().board.remove_dead_minions();
    });

    return new_states;
}
