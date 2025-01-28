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

void Tictactoe::read_move(Client player1, Client player2) {
    while (true) {
        try {
            int position;
            cout << "Player " << (current_player == 1 ? "1 (X)" : "2 (O)") << ", choose one position (1-9): ";
            cout << endl;
            
            if (!(cin >> position)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Invalid input! Please, your number must be a number");
            }

            if (position < 1 || position > 9) {
                 throw std::out_of_range("Invalid! Please, type a number between 1 e 9.");
            }

            int row = (position - 1) / 3;
            int col = (position - 1) % 3;

              // Verifica se a jogada é válida
            if (!is_move_valid(row, col)) {
                throw std::invalid_argument("OCCUPED POSITION, TRY AGAIN");
            }

            if(is_move_valid(row, col)){
                // Atualiza o tabuleiro com o valor do jogador atual
                Board[row][col] = current_player;

               // Alterna o jogador
                current_player *= -1;
                break;
            }

        }

        catch (const runtime_error& e) {
            cout << "Input Error: " << e.what() << endl;
        }
        catch (const std::out_of_range& e) {
            // Trata a exceção de posição fora dos limites
            cout << e.what() << endl;
        } catch (const std::invalid_argument& e) {
            // Trata a exceção de posição ocupada
            cout << e.what() << endl; 
        } 

        cout << "Try again." << endl;
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

void Tictactoe:: test_win_condition(Client player1, Client player2) {

    for (int i = 0; i < 3; i++) { // Verifica linhas, colunas e diagonais
        int rowSum = Board[i][0] + Board[i][1] + Board[i][2];
        int colSum = Board[0][i] + Board[1][i] + Board[2][i];
        int diag1 = Board[0][0] + Board[1][1] + Board[2][2];            
        int diag2 = Board[0][2] + Board[1][1] + Board[2][0];

        if (rowSum == 3 || colSum == 3 || diag1 == 3 || diag2 == 3) {
            is_game_ended = true;
            winner = 1;
            ends_game(player1, player2);
            return;
        }

        if (rowSum == -3 || colSum == -3 || diag1 == -3 || diag2 == -3) {                
            is_game_ended = true;
            winner = -1;
            ends_game(player1, player2);
            return;
        }
    }

    if (has_valid_moves() == false) { // Verifica se empatou
            is_game_ended = true;
            ends_game(player1, player2);
    }

    // Caso contrário, nenhum vencedor e jogo segue
}

void Tictactoe:: ends_game(Client player1, Client player2) {
    if(winner == 1){
        player1.add_status(1);
        player2.add_status(-1);
        cout << player1.get_nickname() << " won!" << endl;

    } else if(winner == -1){
        player1.add_status(-1);
        player2.add_status(1);
        cout << player2.get_nickname() << " won!" << endl;
    }
    else {
        player1.add_status(0);
        player2.add_status(0);
        cout << "DEU VELHA" << endl;
    }
}

void Tictactoe:: play(Client player1, Client player2) {
    while (!is_game_ended) {
        print_board();
        test_win_condition(player1, player2);
        if (is_game_ended) {
            break;
        }
        read_move(player1, player2);
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
 
