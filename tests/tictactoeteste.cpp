#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "tictactoe.hpp"
#include "client.hpp"

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

TEST_CASE("Testando o método read_move") {
    SUBCASE("Jogada válida") {
        Tictactoe game;
        Client p1;
        Client p2;
        InputSimulator sim("1\n");
        game.read_move(p1, p2);

        CHECK(game.get_board(0, 0) == 1); // Jogador 1 faz a jogada
        CHECK(game.get_current_player() == -1); // Alterna para o jogador 2
    }

    SUBCASE("Input inválido (não numérico)") {
        Tictactoe game;
        Client p1;
        Client p2;
        InputSimulator sim("abc\n1\n");
        game.read_move(p1, p2);

        std::string output = sim.getOutput();
        CHECK(output.find("Invalid input") != std::string::npos);
        CHECK(game.get_board(0, 0) == 1); // Jogada correta após erro
    }

    SUBCASE("Jogada fora dos limites") {
        Tictactoe game;
        Client p1;
        Client p2;
        InputSimulator sim("10\n1\n");
        game.read_move(p1, p2);

        std::string output = sim.getOutput();
        CHECK(output.find("Invalid! Please, type a number between 1 e 9.") != std::string::npos);
    }

    SUBCASE("Jogada em posição ocupada") {
        Tictactoe game;
        Client p1;
        Client p2;
        InputSimulator sim("1\n1\n2\n");
        game.read_move(p1, p2);
        game.read_move(p1, p2);

        std::string output = sim.getOutput();
        CHECK(output.find("OCCUPED POSITION, TRY AGAIN") != std::string::npos);
    }
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