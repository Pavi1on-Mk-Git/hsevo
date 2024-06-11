#include "Board.h"

Board::Board() {}

const unsigned int Board::MAX_BOARD_SIZE = 7;

void Board::add_card(std::unique_ptr<Card> card, unsigned int position)
{
    _board.insert(_board.begin() + position, std::move(card));
}

unsigned int Board::minion_count()
{
    return _board.size();
}