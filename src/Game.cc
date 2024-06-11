#include "Game.h"

Game::Game(std::array<AIPlayer, 2> players, std::ranlux24_base& random_engine):
    _random_engine(random_engine), _players(std::move(players)), _game_ended(false), _turn_ended(false)
{}

void Game::check_winner()
{
    bool first_player_dead = _players.at(0).health <= 0;
    bool second_player_dead = _players.at(1).health <= 0;

    if(first_player_dead || second_player_dead)
        _game_ended = true;
    else
        return;

    if(first_player_dead && second_player_dead)
        _winner = std::nullopt;
    else if(first_player_dead)
        _winner = 1;
    else if(second_player_dead)
        _winner = 2;
}

void Game::switch_active_player()
{
    _active_player = 1 - _active_player;
}

AIPlayer& Game::current_player()
{
    return _players.at(_active_player);
}

static constexpr auto first_draw_amount = 3;
static constexpr auto second_draw_amount = 4;

void Game::mulligan()
{
    draw(first_draw_amount);
    switch_active_player();

    draw(second_draw_amount);
    // TODO add The Coin to hand
    switch_active_player();
}

void Game::do_turn()
{
    draw();

    check_winner();
    if(_game_ended)
        return;

    _turn_ended = false;

    while(!_turn_ended)
    {
        auto chosen_action = current_player().choose_action(get_possible_actions());

        chosen_action->apply(*this);

        check_winner();
        if(_game_ended)
            return;
    }

    switch_active_player();
}

void Game::draw(unsigned int amount)
{
    auto [drawn_cards, fatigue_count] = current_player().deck.draw(amount);
    current_player().hand.add_cards(std::move(drawn_cards));
    current_player().fatigue(fatigue_count);
}

void Game::draw()
{
    auto drawn_card = current_player().deck.draw();
    if(drawn_card)
        current_player().hand.add_cards(std::move(drawn_card));
    else
        current_player().fatigue(1);
}

std::vector<std::unique_ptr<Action>> Game::get_possible_actions()
{
    std::vector<std::unique_ptr<Action>> possible_actions;
    for(auto hand_position = 0u; hand_position < current_player().hand.size(); ++hand_position)
    {
        auto minion_count = current_player().board.minion_count();
        if(minion_count == Board::MAX_BOARD_SIZE)
            break;
        for(auto board_position = 0u; board_position <= minion_count; ++board_position)
            possible_actions.push_back(std::make_unique<PlayCardAction>(hand_position, board_position));
    }
    possible_actions.push_back(std::make_unique<EndTurnAction>());

    return possible_actions;
}

std::optional<unsigned int> Game::run()
{
    _active_player = _random_engine() % 2;

    mulligan();
    while(!_game_ended)
        do_turn();

    return _winner;
}

void Game::do_action(const EndTurnAction& action)
{
    static_cast<void>(action);
    _turn_ended = true;
}

void Game::do_action(const PlayCardAction& action)
{
    auto played_card = std::move(current_player().hand.remove_card(action.hand_position));
    current_player().board.add_card(std::move(played_card), action.hand_position);
}