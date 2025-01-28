#ifndef CONNECT4_HPP
#define CONNECT4_HPP

#include "board.hpp"

class Connect4 : public Board {
private:
    int board[6][7];
    int column_height[7];
    int current_player;
    bool is_game_ended;
    int last_move;

public:
    Connect4();
    void print_board() override;
    void read_move(Client player1, Client player2) override;
    bool is_move_valid(int x, int y) override;
    void test_win_condition(Client player1, Client player2) override;
    bool is_there_more_moves();
    void play(Client player1, Client player2);
    bool get_is_game_ended();
    int get_current_player();
    int get_board(int x, int y);
};

#endif // CONNECT4_HPP