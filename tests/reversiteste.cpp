#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>


#include "reversi.hpp"

TEST_CASE("Testando o método is_move_valid") {
    Reversi game;

    SUBCASE("Jogada válida para capturar peças") {
        CHECK(game.is_move_valid(2, 3) == true); // Captura vertical
        CHECK(game.is_move_valid(3, 2) == true); // Captura horizontal
    }

    SUBCASE("Jogada fora dos limites do tabuleiro") {
        CHECK_THROWS_AS(game.is_move_valid(-1, 3), std::invalid_argument);
        CHECK_THROWS_AS(game.is_move_valid(8, 3), std::invalid_argument);
    }

    SUBCASE("Jogada em uma posição já ocupada") {
        CHECK_THROWS_AS(game.is_move_valid(3, 3), std::runtime_error); // Posição ocupada por peça
    }

    SUBCASE("Jogada sem capturar peças do oponente") {
        CHECK(game.is_move_valid(0, 0) == false); // Não captura nenhuma peça
        CHECK(game.is_move_valid(7, 7) == false); // Não captura nenhuma peça
    }
}

TEST_CASE("Testando o método has_valid_moves") {
    Reversi game;

    SUBCASE("Tabuleiro inicial com jogadas válidas disponíveis") {
        CHECK(game.has_valid_moves() == true); // Existem jogadas válidas
    }
}