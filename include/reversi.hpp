#ifndef REVERSI_HPP
#define REVERSI_HPP

#include "board.hpp"

class Reversi : public Board {
private:
    int current_player;
    int board[8][8];
    bool is_game_ended;

public:
    Reversi();

    void print_board() override;
    void read_move() override;
    bool is_move_valid(int x, int y) override;
    bool has_valid_moves();
    void test_win_condition() override;
    void ends_game();
    void play();

    ~Reversi();
};

#endif // REVERSI_HPP