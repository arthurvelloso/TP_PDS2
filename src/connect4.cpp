#include "connect4.hpp"
#include "client.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

/// Inicializador
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

/// Imprimir o tabuleiro
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

/// Realizar jogada
void Connect4:: read_move(Client player1, Client player2){
   
while (true) {
        try {
            cout << "Player " << (current_player == 1 ? player1.get_nickname() : player2.get_nickname()) << ", enter the column you want to play (0-6): ";
            cout << endl;
        
            int move;
            if (!(cin >> move)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Invalid input! Please, your number must be a number");
            }

            if (move < 0 || move > 6) {
                throw std::out_of_range("Invalid! Please, type a number between 0 e 6.");
             }

             if (!is_move_valid(move, 0)) {
                 throw std::invalid_argument("Occupped position, try again");
             }

            if (is_move_valid(move, 0)) {
                last_move = move;
                board[column_height[move]][move] = current_player;
                test_win_condition(player1, player2);
                column_height[move]--;
                current_player = -current_player;
                break;
            }
            else{
                cout << "Error: This is not a valid move." << endl;
            }
        }
        catch (const invalid_argument& e) {
            cout << "Input Error: " << e.what() << endl;
        }

        catch (const out_of_range& e) {
            cout << "Input Error: " << e.what() << endl;
        }

        catch (const runtime_error& e) {
            cout << "Input Error: " << e.what() << endl;
        }

        cout << "Try again." << endl;
    }

}

/// Testar se jogada é válida
bool Connect4::is_move_valid(int move, int y) {
    return move >= 0 && move < 7 && column_height[move] >= 0;
}

/// Testar vitória
void Connect4::test_win_condition(Client player1, Client player2) {
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
                    cout << (current_player == 1 ? player1.get_nickname() : player2.get_name()) << " wins!" << endl;
                    if (current_player == 1) {
                        player1.add_status(1);
                        player2.add_status(-1);
                    }
                    else {
                        player1.add_status(-1);
                        player2.add_status(1);
                    }
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
                    cout << (current_player == 1 ? player1.get_nickname() : player2.get_name()) << " wins!" << endl;
                    if (current_player == 1) {
                        player1.add_status(1);
                        player2.add_status(-1);
                    }
                    else {
                        player1.add_status(-1);
                        player2.add_status(1);
                    }
                    is_game_ended = true;
                    return;
                }
            }
            total = 1;
        }
    }
}

/// Checar se o tabuleiro está cheio
bool Connect4::is_there_more_moves() {
    int filled_columns = 0;
    for (int i = 0; i < 6; i++) {
        if (column_height[i] == 6) {
            filled_columns++;
        }
    }
    return filled_columns != 6;
}

/// Iniciar um jogo
void Connect4::play(Client player1, Client player2) {
    while (!is_game_ended) {
        print_board();
        read_move(player1, player2);
    }
    print_board();
}

bool Connect4::get_is_game_ended() {
    return is_game_ended;
}

int Connect4::get_current_player() {
    return current_player;
}

int Connect4::get_board(int x, int y) {
    if (x < 0 || x >= 8 || y < 0 || y >= 8) {
        throw std::invalid_argument("Coordinates must be between 0 and 7.");
    }
    return board[x][y];
}
