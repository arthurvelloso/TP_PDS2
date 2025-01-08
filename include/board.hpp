#ifndef BOARD_H
#define BOARD_H

#include <iostream>


class Board {
private:



public:
    Board();

    void print_board();
    void read_move();
    bool is_move_valid();
    void test_win_condition();

    ~Board();
};



#endif //BOARD_H