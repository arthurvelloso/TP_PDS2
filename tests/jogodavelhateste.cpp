#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <sstream>
#include "velha.hpp" // Inclua o arquivo de cabeçalho da classe

TEST_CASE("Jogodavelha - Teste do método is_move_valid") {
    Jogodavelha jogo;

    SUBCASE("Tabuleiro vazio - Todas as posições são válidas") {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                CHECK(jogo.is_move_valid(i, j) == true); // Todas as posições devem estar disponíveis
            }
        }
    }
}