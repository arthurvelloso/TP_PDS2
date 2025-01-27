#include "connect4.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

// Inicializador
Connect4::Connect4() {
    for (int i = 0; i < 7; i++) {
        column_height[i] = 5;
        for (int j = 0; j < 6; j++) {
            board[j][i] = 0;
        }
    }

    current_player = 1;
    is_game_ended = false;
    last_move = -1; 
}

// Imprimir o tabuleiro
void Connect4::print_board() {
    cout << "  0 1 2 3 4 5 6" << endl;
    for (int i = 0; i < 6; i++) {
        cout << i << " ";
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == 1) {
                cout << "B ";
            } else if (board[i][j] == -1) {
                cout << "W ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

// Realizar jogada
void Connect4:: read_move(){
    int move;
    bool valid_input = false;

    
    try {  
        cout << "Player " << (current_player == 1 ? "1 (X)" : "2 (O)") << ", enter the column you want to play (0-6): "; 
        cin >> move;
        cout << endl;     

        // Verifica se a entrada é inválida (não é um número inteiro)
        if (cin.fail()) {
            cin.clear(); // Limpa o estado de erro do cin
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar a entrada inválida
            throw std::invalid_argument("Invalid input! Please, your number must be a number");
        }

        // Verifica se a posição está fora dos limites válidos
        if (move < 0 || move > 6) {
            throw std::out_of_range("Invalid! Please, type a number between 1 e 9.");
        }

        if (!is_move_valid(0, move)) {
            throw std::invalid_argument("Occupped position, try again");
        }

        last_move = move;
        board[column_height[move]][move] = current_player;
        test_win_condition();
        column_height[move]--;
        current_player = -current_player;
        valid_input = true;
    }
    catch (const std::out_of_range& e) {
        // Trata a exceção de posição fora dos limites
        cout << e.what() << endl;
        read_move(); // Solicita outra jogada

    } catch (const std::invalid_argument& e) {
        // Trata a exceção de posição ocupada
        cout << e.what() << endl;
        read_move(); // Solicita outra jogada
    }
    catch (...) {
        // Tratamento genérico para exceções inesperadas
        cout << "Inesperated error. Try again a new play." << endl;
        read_move(); // Solicita outra jogada
    }
}

// Testar se jogada é válida
bool Connect4::is_move_valid(int move, int y) {
    return move >= 0 && move < 7 && column_height[move] >= 0;
}

// Testar vitória
void Connect4::test_win_condition() {
    int move = last_move;
    if(move < 0 || move > 7) {
        return;
    }

    int total = 1;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            if (i == 0 && j == 0) {
                j++;
            }
            int posx = column_height[move] + i;
            int posy = move + j;
            while (board[posx][posy] == current_player && posx >= 0 && posx < 7 && posy >= 0 && posy < 6) {
                total++;
                posx += i;
                posy += j;
                if (total == 4) {
                    cout << (current_player == 1 ? "Black" : "White") << " player wins!" << endl;
                    is_game_ended = true;
                    return;
                }
            }
            posx = column_height[move] - i;
            posy = move - j;
            while (board[posx][posy] == current_player && posx >= 0 && posx < 7 && posy >= 0 && posy < 6) {
                total++;
                posx -= i;
                posy -= j;
                if (total == 4) {
                    cout << (current_player == 1 ? "Black" : "White") << " player wins!" << endl;
                    is_game_ended = true;
                    return;
                }
            }
            total = 1;
        }
    }
}

// Checar se o tabuleiro está cheio
bool Connect4::is_there_more_moves() {
    int filled_columns = 0;
    for (int i = 0; i < 6; i++) {
        if (column_height[i] == 6) {
            filled_columns++;
        }
    }
    return filled_columns != 6;
}

// Iniciar um jogo
void Connect4::play() {
    while (!is_game_ended) {
        print_board();
        read_move();
    }
    print_board();
}
