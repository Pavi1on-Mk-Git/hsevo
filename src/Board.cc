#include "Board.h"

#include <algorithm>

const unsigned int Board::MAX_BOARD_SIZE = 7;

Board::Board()
{
    _board.reserve(MAX_BOARD_SIZE);
}

Board::Board(const Board& board)
{
    _board.reserve(MAX_BOARD_SIZE);
    std::transform(board._board.begin(), board._board.end(), std::back_inserter(_board), [](const auto& card) {
        return std::make_unique<Card>(*card);
    });
}

void Board::add_card(std::unique_ptr<Card> card, unsigned int position)
{
    _board.insert(_board.begin() + position, std::move(card));
}

unsigned int Board::minion_count()
{
    return _board.size();
}

std::unique_ptr<Card>& Board::get_minion(unsigned int position)
{
    return _board.at(position);
}

void Board::remove_dead_minions()
{
    auto new_end = std::remove_if(_board.begin(), _board.end(), [](const auto& minion) { return minion->health <= 0; });
    _board.erase(new_end, _board.end());
}