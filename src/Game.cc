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

AIPlayer& Game::opponent()
{
    return _players.at(1 - _active_player);
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

    current_player().mana = ++current_player().mana_crystals;

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

        auto card_cost = current_player().hand.get_card(hand_position)->mana_cost;

        if(card_cost > current_player().mana)
            continue;

        for(auto board_position = 0u; board_position <= minion_count; ++board_position)
            possible_actions.push_back(std::make_unique<PlayCardAction>(hand_position, board_position, card_cost));
    }

    for(auto current_board_position = 0u; current_board_position < current_player().board.minion_count();
        ++current_board_position)
    {
        possible_actions.push_back(std::make_unique<HitHeroAction>(current_board_position));

        for(auto opponent_board_position = 0u; opponent_board_position < opponent().board.minion_count();
            ++opponent_board_position)
            possible_actions.push_back(std::make_unique<TradeAction>(current_board_position, opponent_board_position));
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
    current_player().board.add_card(std::move(played_card), action.board_position);
    current_player().mana -= action.card_cost;
}

void Game::do_action(const TradeAction& action)
{
    auto& first_minion = current_player().board.get_minion(action.first_target);
    auto& second_minion = opponent().board.get_minion(action.second_target);

    first_minion->health -= second_minion->attack;
    second_minion->health -= first_minion->attack;

    current_player().board.remove_dead_minions();
    opponent().board.remove_dead_minions();
}

void Game::do_action(const HitHeroAction& action)
{
    opponent().health -= current_player().board.get_minion(action.position)->attack;
}