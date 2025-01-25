#ifndef JOGODAVELHA_HPP
#define REVERSI_HPP

#include "board.hpp"

class Jogodavelha : public Board {
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
    Jogodavelha();

    void print_board() override;
    void read_move() override;
    bool is_move_valid(int x, int y) override;
    bool has_valid_moves();
    void test_win_condition() override;
    void ends_game();
    void play();

    ~Jogodavelha();
};

#endif