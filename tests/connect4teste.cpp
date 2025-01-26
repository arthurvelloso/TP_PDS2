#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "connect4.hpp"

TEST_CASE("Testando o método is_move_valid") {
    Connect4 game;

    SUBCASE("Jogada válida") {
        CHECK(game.is_move_valid(0, 0) == true);
        CHECK(game.is_move_valid(6, 0) == true); 
    }

    SUBCASE("Jogada fora dos limites do tabuleiro") {
        CHECK(game.is_move_valid(-1, 0) == false); 
        CHECK(game.is_move_valid(7, 0) == false);  
    }

}

TEST_CASE("Testando o método is_there_more_moves") {
    Connect4 game;

    SUBCASE("Tabuleiro inicial com movimentos disponíveis") {
        CHECK(game.is_there_more_moves() == true);
    }

}