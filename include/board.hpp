#ifndef BOARD_H
#define BOARD_H

#include <iostream>


class Board {
private:


public:
    Board();

    virtual void print_board();
    virtual void read_move();
    virtual bool is_move_valid(int x, int y);
    virtual void test_win_condition();


    ~Board();
};



#endif //BOARD_H