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
    Board(const Board& board);
    void add_card(std::unique_ptr<Card> card, unsigned int position);
    unsigned int minion_count();
    std::unique_ptr<Card>& get_minion(unsigned int position);
    void remove_dead_minions();
};

#endif