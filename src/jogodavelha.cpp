#include "jogodavelha.hpp"
#include <iostream>

using namespace std;

Jogodavelha:: Jogodavelha() {
    is_game_ended = false;
    current_player = 1;
    winner = 0;
}

void Jogodavelha:: print_board() {
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

void Jogodavelha:: read_move() {
    int position;

    // Pede a jogada do jogador
    cout << "Jogador " << (current_player == 1 ? "1 (X)" : "2 (O)") << ", escolha uma posição (1-9): ";
    cin >> position;
    cout << endl;

    if (position < 1 || position > 9) {
        cout << "Posição inválida! Escolha um número entre 1 e 9." << endl;
    }

    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    if (is_move_valid(row, col)) {
        Board[row][col] = current_player; // Atualiza com o valor do jogador
        current_player *= (-1); // Inverte a vez do jogador após sua jogada

    } else {
        cout << "POSIÇÃO OCUPADA, TENTE OUTRA" << endl;
        read_move(); // Chama novamente a jogada
    }
}

bool Jogodavelha:: is_move_valid(int x, int y) {
    return Board[x][y] == 0; // A função simplesmente retorna o valor-verdade dessa igualdade.
}

bool Jogodavelha:: has_valid_moves() {
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

void Jogodavelha:: test_win_condition() {

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

void Jogodavelha:: ends_game() {
    if(winner == 1){
        cout << "Jogador 1 venceu!" << endl;

    } else if(winner == -1){
        cout << "Jogador 2 venceu!" << endl;
    }
    else {
        cout << "DEU VELHA" << endl;
    }
}

void Jogodavelha:: play() {
    while (!is_game_ended) {
        print_board();
        test_win_condition();
        if (is_game_ended) {
            break;
        }
        read_move();
    }
}

Jogodavelha:: ~Jogodavelha() {}
 