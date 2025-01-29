/// Board class
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "client.hpp"

/// Classe Board
class Board {
private:


public:
    Board();

    virtual void print_board();
    virtual void read_move(Client player1, Client player2);
    virtual bool is_move_valid(int x, int y);
    virtual void test_win_condition(Client player1, Client player2);

    ~Board();
};



#endif //BOARD_H