#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "tictactoe.hpp" // Inclua o arquivo de cabeçalho da classe

TEST_CASE("Testando o construtor de Tictactoe") {
    Tictactoe game;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(game.get_board(i, j) == 0);
        }
    }

    // Verifica o jogador inicial
    CHECK(game.get_current_player() == 1);

    // Verifica se o jogo não terminou inicialmente
    CHECK(game.get_is_game_ended() == false);
}

TEST_CASE("Tictactoe - Teste do método is_move_valid") {
    Tictactoe jogo;

    SUBCASE("Tabuleiro vazio - Todas as posições são válidas") {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                CHECK(jogo.is_move_valid(i, j) == true); // Todas as posições devem estar disponíveis
            }
        }
    }
}