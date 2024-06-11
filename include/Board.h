#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>

#include "Card.h"

class Board
{
private:
    std::vector<std::unique_ptr<Card>> _board;
public:
    static const unsigned int MAX_BOARD_SIZE;

    Board();
    void add_card(std::unique_ptr<Card> card, unsigned int position);
    unsigned int minion_count();
};

#endif