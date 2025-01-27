#include "tictactoe.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

Tictactoe:: Tictactoe() {
    is_game_ended = false;
    current_player = 1;
    winner = 0;
}

void Tictactoe:: print_board() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (Board[i][j] == 1) {
                cout << " X ";
            } else if (Board[i][j] == -1) {
                cout << " O ";
            } else {
                cout << "   ";
            }
            if (j < 2) cout << "|"; // Adiciona separadores de colunas
        }
        cout << endl;
        if (i < 2) cout << "---+---+---" << endl; // Adiciona linha separadora
    }
}

void Tictactoe::read_move() {
    int position;

    try {
        // Pede a jogada do jogador
        cout << "Player " << (current_player == 1 ? "1 (X)" : "2 (O)") << ", choose one position (1-9): ";
        cin >> position;
        cout << endl;

        // Verifica se a entrada é inválida (não é um número inteiro)
        if (cin.fail()) {
            cin.clear(); // Limpa o estado de erro do cin
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar a entrada inválida
            throw std::invalid_argument("Invalid input! Please, your number must be a number");
        }

        // Verifica se a posição está fora dos limites válidos
        if (position < 1 || position > 9) {
            throw std::out_of_range("Invalid! Please, type a number between 1 e 9.");
        }

        // Converte a posição para índices de linha e coluna
        int row = (position - 1) / 3;
        int col = (position - 1) % 3;

        // Verifica se a jogada é válida
        if (!is_move_valid(row, col)) {
            throw std::invalid_argument("OCCUPED POSITION, TRY AGAIN");
        }

        // Atualiza o tabuleiro com o valor do jogador atual
        Board[row][col] = current_player;

        // Alterna o jogador
        current_player *= -1;

    } catch (const std::out_of_range& e) {
        // Trata a exceção de posição fora dos limites
        cout << e.what() << endl;
        read_move(); // Solicita outra jogada

    } catch (const std::invalid_argument& e) {
        // Trata a exceção de posição ocupada
        cout << e.what() << endl;
        read_move(); // Solicita outra jogada  
    }    
}

bool Tictactoe:: is_move_valid(int x, int y) {
    return Board[x][y] == 0;
}

bool Tictactoe:: has_valid_moves() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (Board[i][j] == 0) {
                return true; // Ainda há pelo menos uma casa vazia
            }
        }
    }
    is_game_ended = true;
    return false; // Todas as casas estão preenchidas
}

void Tictactoe:: test_win_condition() {

    for (int i = 0; i < 3; i++) { // Verifica linhas, colunas e diagonais
        int rowSum = Board[i][0] + Board[i][1] + Board[i][2];
        int colSum = Board[0][i] + Board[1][i] + Board[2][i];
        int diag1 = Board[0][0] + Board[1][1] + Board[2][2];            
        int diag2 = Board[0][2] + Board[1][1] + Board[2][0];

        if (rowSum == 3 || colSum == 3 || diag1 == 3 || diag2 == 3) {
            is_game_ended = true;
            winner = 1;
            ends_game();
            return;
        }

        if (rowSum == -3 || colSum == -3 || diag1 == -3 || diag2 == -3) {                
            is_game_ended = true;
            winner = -1;
            ends_game();
            return;
        }
    }

    if (has_valid_moves() == false) { // Verifica se empatou
            is_game_ended = true;
            ends_game();
    }

    // Caso contrário, nenhum vencedor e jogo segue
}

void Tictactoe:: ends_game() {
    if(winner == 1){
        cout << "Player 1 won!" << endl;

    } else if(winner == -1){
        cout << "Player 2 won!" << endl;
    }
    else {
        cout << "DEU VELHA" << endl;
    }
}

void Tictactoe:: play() {
    while (!is_game_ended) {
        print_board();
        test_win_condition();
        if (is_game_ended) {
            break;
        }
        read_move();
    }
}

bool Tictactoe::get_is_game_ended() {
    return is_game_ended;
}

int Tictactoe::get_current_player() {
    return current_player;
}

int Tictactoe::get_board(int x, int y) {
    if (x < 0 || x >= 8 || y < 0 || y >= 8) {
        throw std::invalid_argument("Coordinates must be between 0 and 7.");
    }
    return Board[x][y];
}

Tictactoe:: ~Tictactoe() {}
 
