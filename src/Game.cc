#include "Game.h"

Game::Game(std::array<AIPlayer, 2> players, std::ranlux24_base& random_engine):
    _random_engine(random_engine), _players(std::move(players)), _game_ended(false)
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

static constexpr auto first_draw_amount = 3;
static constexpr auto second_draw_amount = 4;

void Game::mulligan()
{
    draw(first_draw_amount);
    switch_active_player();

    draw(second_draw_amount);
    switch_active_player();

    // TODO add The Coin to hand
}

void Game::do_turn()
{
    draw();

    check_winner();
    if(_game_ended)
        return;

    switch_active_player();
}

void Game::draw(unsigned int amount)
{
    auto [drawn_cards, fatigue_count] = _players.at(_active_player).deck.draw(amount);
    _players.at(_active_player).hand.add_cards(std::move(drawn_cards));
    _players.at(_active_player).fatigue(fatigue_count);
}

void Game::draw()
{
    auto drawn_card = _players.at(_active_player).deck.draw();
    if(drawn_card)
        _players.at(_active_player).hand.add_cards(std::move(drawn_card));
    else
        _players.at(_active_player).fatigue(1);
}

std::optional<unsigned int> Game::run()
{
    _active_player = _random_engine() % 2;

    mulligan();
    while(!_game_ended)
        do_turn();

    return _winner;
}