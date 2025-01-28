#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP
#include "board.hpp"
#include "client.hpp"

class Tictactoe : public Board {
private:
    int Board[3][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
    };
    bool is_game_ended;
    int current_player;
    int winner;

public:
    Tictactoe();

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

    ~Tictactoe();
};

#endif
