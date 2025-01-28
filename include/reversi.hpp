#ifndef REVERSI_HPP
#define REVERSI_HPP

#include "board.hpp"
#include "client.hpp"

class Reversi : public Board {
private:
    int current_player;
    int board[8][8];
    bool is_game_ended;

public:
    Reversi();

    void print_board() override;
    void read_move(Client player1, Client player2) override;
    bool is_move_valid(int x, int y) override;
    bool has_valid_moves();
    void test_win_condition(Client player1, Client player2) override;
    void ends_game(Client player1, Client player2);
    void play(Client player1, Client player2);
    bool get_is_game_ended();
    int get_current_player();
    int get_board(int x, int y);

    ~Reversi();
};

#endif // REVERSI_HPP