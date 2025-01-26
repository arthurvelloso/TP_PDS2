#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>


#include "reversi.hpp"

TEST_CASE("Construtor") {
        Reversi game;
        
        CHECK(game.get_board(3, 3) == 1); 
        CHECK(game.get_board(4, 4) == 1);   
        CHECK(game.get_board(3, 4) == -1); 
        CHECK(game.get_board(4, 3) == -1);  
        
        // Verifica se o restante do tabuleiro está vazio
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if ((i != 3 || j != 3) && 
                    (i != 3 || j != 4) && 
                    (i != 4 || j != 3) && 
                    (i != 4 || j != 4)) {
                    CHECK(game.get_board(i, j) == 0);
                }
            }
        }
        
        // Estado inicial do jogo
        CHECK(game.get_current_player() == -1);  
        CHECK(game.get_is_game_ended() == false);
    }

TEST_CASE("Testando o método is_move_valid") {
    Reversi game;

    SUBCASE("Jogada válida para capturar peças") {
        CHECK(game.is_move_valid(2, 3) == true); // Captura vertical
        CHECK(game.is_move_valid(3, 2) == true); // Captura horizontal
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

TEST_CASE("Testando o método ends_game") {
        Reversi game;
            game.ends_game();
            CHECK(game.get_is_game_ended() == true);
    
    }