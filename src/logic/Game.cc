#include "logic/Game.h"

#include <algorithm>

#include "utils/Rng.h"

Game::Game(const std::unique_ptr<PlayerLogic>& first_player, const std::unique_ptr<PlayerLogic>& second_player):
    players_({first_player, second_player}), game_ended_(false), turn_ended_(false)
{}

void Game::check_winner()
{
    bool first_player_dead = players_.at(0).state.health <= 0;
    bool second_player_dead = players_.at(1).state.health <= 0;

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

void Game::do_turn()
{
    draw();

    check_winner();
    if(game_ended_)
        return;

    current_player().state.mana = ++current_player().state.mana_crystals;

    for(unsigned minion_index = 0; minion_index < current_player().state.board.minion_count(); ++minion_index)
        current_player().state.board.get_minion(minion_index).active = true;

    turn_ended_ = false;

    while(!turn_ended_)
    {
        auto chosen_action = current_player().logic->choose_action(*this, get_possible_actions());

        chosen_action->apply(*this);

        check_winner();
        if(game_ended_)
            return;
    }

    switch_active_player();
}

void Game::draw(unsigned amount)
{
    auto [drawn_cards, fatigue_count] = current_player().state.deck.draw(amount);
    current_player().state.hand.add_cards(std::move(drawn_cards));
    current_player().state.fatigue(fatigue_count);
}

void Game::draw()
{
    auto drawn_card = current_player().state.deck.draw();
    if(drawn_card)
        current_player().state.hand.add_cards(std::move(drawn_card));
    else
        current_player().state.fatigue(1);
}

std::vector<std::unique_ptr<Action>> Game::get_possible_actions()
{
    std::vector<std::unique_ptr<Action>> possible_actions;
    for(unsigned hand_position = 0; hand_position < current_player().state.hand.size(); ++hand_position)
    {
        auto& current_card = current_player().state.hand.get_card(hand_position);
        auto play_card_actions = current_card->create_play_actions_func(current_card, *this, hand_position);
        std::move(play_card_actions.begin(), play_card_actions.end(), std::back_inserter(possible_actions));
    }

    auto attack_actions = get_attack_actions();
    std::move(attack_actions.begin(), attack_actions.end(), std::back_inserter(possible_actions));

    possible_actions.push_back(std::make_unique<EndTurnAction>());

    return possible_actions;
}

std::vector<std::unique_ptr<Action>> Game::get_attack_actions()
{
    std::vector<std::unique_ptr<Action>> attack_actions;

    std::vector<unsigned> taunt_minion_positions;

    for(unsigned opponent_board_position = 0; opponent_board_position < opponent().state.board.minion_count();
        ++opponent_board_position)
        if(opponent().state.board.get_minion(opponent_board_position).keywords & TAUNT)
            taunt_minion_positions.push_back(opponent_board_position);

    for(unsigned current_board_position = 0; current_board_position < current_player().state.board.minion_count();
        ++current_board_position)
    {
        auto& current_minion = current_player().state.board.get_minion(current_board_position);
        if(!current_minion.active || current_minion.keywords & CANT_ATTACK)
            continue;

        if(taunt_minion_positions.empty())
        {
            attack_actions.push_back(std::make_unique<HitHeroAction>(current_board_position));

            for(unsigned opponent_board_position = 0; opponent_board_position < opponent().state.board.minion_count();
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

PlayerStateInput Game::get_player_state(unsigned player_index)
{
    HeroStateInput hero_state{static_cast<unsigned>(players_.at(player_index).state.health)};
    std::array<MinionStateInput, Board::MAX_BOARD_SIZE> minion_states;

    const unsigned board_size = players_.at(player_index).state.board.minion_count();
    for(unsigned minion_index = 0; minion_index < board_size; ++minion_index)
    {
        auto& curr_minion = players_.at(player_index).state.board.get_minion(minion_index);
        minion_states.at(minion_index
        ) = MinionStateInput{static_cast<unsigned>(curr_minion.health), curr_minion.attack};
    }
    for(unsigned empty_space_index = board_size; empty_space_index < Board::MAX_BOARD_SIZE - board_size;
        ++empty_space_index)
        minion_states.at(empty_space_index) = MinionStateInput();

    return PlayerStateInput{
        hero_state, minion_states, players_.at(player_index).state.hand.size(), board_size,
        players_.at(player_index).state.mana};
}

GameResult Game::run()
{
    active_player_ = Rng::instance()->uniform_int(0, 1);

    mulligan();
    while(!game_ended_)
        do_turn();

    return winner_;
}

Game Game::copy() const
{
    return Game(*this);
}

GameStateInput Game::get_state()
{
    return GameStateInput{{get_player_state(active_player_), get_player_state(1 - active_player_)}};
}

void Game::do_action(const EndTurnAction& action)
{
    static_cast<void>(action);
    turn_ended_ = true;
}

void Game::do_action(const PlayCardAction& action)
{
    auto played_card = current_player().state.hand.remove_card(action.hand_position);
    current_player().state.board.add_minion(Minion(*played_card), action.board_position);
    current_player().state.mana -= action.card_cost;
    played_card->on_play_func(*this, action.args);
}

void Game::do_action(const TradeAction& action)
{
    auto& first_minion = current_player().state.board.get_minion(action.first_target);
    auto& second_minion = opponent().state.board.get_minion(action.second_target);

    first_minion.health -= second_minion.attack;
    second_minion.health -= first_minion.attack;

    current_player().state.board.remove_dead_minions();
    opponent().state.board.remove_dead_minions();
}

void Game::do_action(const HitHeroAction& action)
{
    opponent().state.health -= current_player().state.board.get_minion(action.position).attack;
}