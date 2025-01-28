#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "client.hpp"
#include "reversi.hpp"

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

TEST_CASE("Testando o método read_move") {
    SUBCASE("Input valido") {
        Reversi game;
        Client p1;
        Client p2;
        InputSimulator sim("2 3\n");
        game.read_move(p1, p2);
        
        // Confere se jogada foi feita corretamente
        CHECK(game.get_board(2, 3) == -1);
        CHECK(game.get_current_player() == 1);
    }

    SUBCASE("Jogada nao numerica") {
        Reversi game;
        Client p1;
        Client p2;
        InputSimulator sim("ab cd\n2 3\n");
        game.read_move(p1, p2);
        
        //Confere mensagem de erro
        std::string output = sim.getOutput();
        CHECK(output.find("Input Error") != std::string::npos);
    }

    SUBCASE("Jogada fora do tabuleiro") {
        Reversi game;
        Client p1;
        Client p2;
        InputSimulator sim("8 8\n2 3\n");
        game.read_move(p1, p2);
        
        //Confere mensagem de erro
        std::string output = sim.getOutput();
        CHECK(output.find("Coordinates must be between 0 and 7") != std::string::npos);
    }

    SUBCASE("Jogada em espaco ocupado") {
        Reversi game;
        Client p1;
        Client p2;
        InputSimulator sim("3 3\n2 3\n");
        game.read_move(p1, p2);
        
        //Confere mensagem de erro
        std::string output = sim.getOutput();
        CHECK(output.find("Selected square is already occupied") != std::string::npos);
    }

    SUBCASE("Jogada invalida - nao captura pecas") {
        Reversi game;
        Client p1;
        Client p2;
        InputSimulator sim("0 0\n2 3\n");
        game.read_move(p1, p2);
        
        //Confere mensagem de erro
        std::string output = sim.getOutput();
        CHECK(output.find("This is not a valid move") != std::string::npos);
    }

    SUBCASE("Varias jogadas invalidas antes de jogada valida") {
        Reversi game;
        Client p1;
        Client p2;
        InputSimulator sim("ab cd\n9 9\n3 3\n0 0\n2 3\n");
        game.read_move(p1, p2);
        
        //Confere se jogada foi feita corretamente
        CHECK(game.get_board(2, 3) == -1);
        CHECK(game.get_current_player() == 1);
    }

    SUBCASE("Varias jogadas validas") {
        Reversi game;
        Client p1;
        Client p2;
        InputSimulator sim("2 3\n4 2\n");
        game.read_move(p1, p2);
        game.read_move(p1, p2);
        
        //Confere se jogada foi feita corretamente
        CHECK(game.get_board(2, 3) == -1);
        CHECK(game.get_board(4, 2) == 1);
    }
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

/*TEST_CASE("Testando o método ends_game") {
        Reversi game;
        Client p1;
        Client p2;
            game.ends_game(p1, p2);
            CHECK(game.get_is_game_ended() == true);
    
    }*/