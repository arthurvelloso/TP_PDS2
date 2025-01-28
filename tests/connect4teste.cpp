#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "connect4.hpp"

class InputSimulator {
private:
    std::streambuf* originalCin;
    std::streambuf* originalCout;
    std::stringstream simulatedInput;
    std::stringstream simulatedOutput;

public:
    InputSimulator(const std::string& input) {
        originalCin = std::cin.rdbuf();
        originalCout = std::cout.rdbuf();
        simulatedInput.str(input);
        std::cin.rdbuf(simulatedInput.rdbuf());
        std::cout.rdbuf(simulatedOutput.rdbuf());
    }

    ~InputSimulator() {
        std::cin.rdbuf(originalCin);
        std::cout.rdbuf(originalCout);
    }

    std::string getOutput() {
        return simulatedOutput.str();
    }
};

TEST_CASE("Testando o construtor") {
    Connect4 game;

    // Testando o estado inicial do tabuleiro
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            CHECK(game.get_board(i, j) == 0); // Tabuleiro vazio
        }
    }

    // Testando configurações iniciais do jogo
    CHECK(game.get_current_player() == 1); // Jogador inicial é o jogador 1
    CHECK(game.get_is_game_ended() == false); // Jogo ainda não acabou
}

TEST_CASE("Testando o método read_move") {
    SUBCASE("Jogada válida") {
        Connect4 game;
        InputSimulator sim("3\n");
        game.read_move();

        // Verifica se a jogada foi realizada corretamente
        CHECK(game.get_board(5, 3) == 1); // A ficha do jogador 1 foi colocada na posição mais baixa da coluna 3
        CHECK(game.get_current_player() == -1); // Agora é a vez do jogador 2
    }

   SUBCASE("Jogada inválida: coluna fora do tabuleiro") {
        Connect4 game;
        InputSimulator sim("8\n3\n");
        game.read_move();

        std::string output = sim.getOutput();
        CHECK(output.find("Invalid! Please, type a number between 0 e 6.") != std::string::npos);
    }

    SUBCASE("Jogada inválida: coluna negativa") {
        Connect4 game;
        InputSimulator sim("-1\n3\n");
        game.read_move();

        std::string output = sim.getOutput();
        CHECK(output.find("Invalid! Please, type a number between 0 e 6.") != std::string::npos);
    }

        SUBCASE("Jogada inválida: coluna cheia") {
         Connect4 game;
         InputSimulator sim("3\n3\n3\n3\n3\n3\n3\n2\n"); 

        for (int i = 0; i < 7; i++) {
            game.read_move();
    }


    std::string output = sim.getOutput();
    CHECK(output.find("Occupped position, try again") != std::string::npos);
    }

}

TEST_CASE("Testando o método is_move_valid") {
    Connect4 game;

    SUBCASE("Jogada válida") {
        CHECK(game.is_move_valid(3, 0) == true);
    }

    SUBCASE("Jogada inválida: coluna fora dos limites") {
        CHECK(game.is_move_valid(-1, 0) == false);
        CHECK(game.is_move_valid(7, 0) == false);
    }

}

TEST_CASE("Testando o método is_there_more_moves") {
    Connect4 game;

    SUBCASE("Tabuleiro inicial com jogadas válidas disponíveis") {
        CHECK(game.is_there_more_moves() == true); // Existem jogadas válidas
    }

}