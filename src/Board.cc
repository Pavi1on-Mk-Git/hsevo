#include "Board.h"

#include <algorithm>

Board::Board()
{
    _board.reserve(MAX_BOARD_SIZE);
}

void Board::add_minion(const Minion& minion, unsigned int position)
{
    _board.insert(_board.begin() + position, std::move(minion));
}

unsigned int Board::minion_count()
{
    return _board.size();
}

Minion& Board::get_minion(unsigned int position)
{
    return _board.at(position);
}

void Board::remove_dead_minions()
{
    auto new_end = std::remove_if(_board.begin(), _board.end(), [](const auto& minion) { return minion.health <= 0; });
    _board.erase(new_end, _board.end());
}