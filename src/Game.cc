#include "Game.h"

Game::Game(std::array<AIPlayer, 2> players, std::ranlux24_base& random_engine):
    _random_engine(random_engine), _players(std::move(players)), _game_ended(false)
{}

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
    switch_active_player();
}

void Game::draw(unsigned int amount)
{
    auto drawn_cards = _players.at(_active_player).deck.draw(amount);
    _players.at(_active_player).hand.add_cards(std::move(drawn_cards));
}

void Game::draw()
{
    auto drawn_card = _players.at(_active_player).deck.draw();
    _players.at(_active_player).hand.add_cards(std::move(drawn_card));
}

void Game::run()
{
    _active_player = 0;

    mulligan();
    while(!_game_ended)
        do_turn();
}