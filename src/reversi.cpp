#include "reversi.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

Reversi::Reversi() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = 0;
        }
    }
    board[3][3] = 1;
    board[4][4] = 1;
    board[3][4] = -1;
    board[4][3] = -1;
    is_game_ended = false;
    current_player = -1;
}

bool Reversi::is_move_valid(int x, int y) {

    if (x < 0 || x >= 8 || y < 0 || y >= 8){
        return false;
    }

    if(board[x][y] != 0){
        return false;
    }

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int posx = x + i;
            int posy = y + j;
            while (posx >= 0 && posx < 8 && posy >= 0 && posy < 8 && board[posx][posy] == -current_player) {
                posx += i;
                posy += j;
                if (board[posx][posy] == current_player) {
                    return true;
                }
            }
        }
    }
    return false;

}

void Reversi::print_board() {
    cout << "  0 1 2 3 4 5 6 7" << endl;
    for (int i = 0; i < 8; i++) {
        cout << i << " ";
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == 0) {
                cout << ". ";
            } else if (board[i][j] == 1) {
                cout << "W ";
            } else if (board[i][j] == -1) {
                cout << "B ";
            }
        }
        cout << endl;
    }
}

void Reversi::read_move(Client player1, Client player2) {
    while (true) {
        try {
            cout << (current_player == 1 ? player1.get_nickname() : player2.get_nickname()) << "'s turn " << (current_player == 1 ? "(White)" : "(Black)") << endl;
            cout << "Enter row (0-7) and column (0-7) separated by space: ";
            
            int x, y;
            if (!(cin >> x >> y)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Input must be two whole numbers separated by space.");
            }

            if (x < 0 || x >= 8 || y < 0 || y >= 8) {
                throw invalid_argument("Coordinates must be between 0 and 7.");
            }

            if (board[x][y] != 0) {
                throw out_of_range("Selected square is already occupied.");
            }

            if (is_move_valid(x, y)) {
                board[x][y] = current_player;
                
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        int posx = x + i;
                        int posy = y + j;
                        while (board[posx][posy] == -current_player && posx >= 0 && posx < 8 && posy >= 0 && posy < 8) {
                            posx += i;
                            posy += j;
                            if (board[posx][posy] == current_player) {
                                posx = x + i;
                                posy = y + j;
                                while (board[posx][posy] == -current_player) {
                                    board[posx][posy] = current_player;
                                    posx += i;
                                    posy += j;
                                }
                            }
                        }
                    }
                }
                current_player = -current_player;
                break;
            }
            else{
                cout << "Error: This is not a valid move. Ensure it captures opponent pieces." << endl;
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


bool Reversi::has_valid_moves() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (is_move_valid(i, j)) {
                return true;
            }
        }
    }
    return false;
}

void Reversi::ends_game(Client player1, Client player2) {
    int sum_pieces = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sum_pieces += board[i][j];
        }
    }
    if (sum_pieces > 0) {
        player1.add_status(1);
        player2.add_status(-1);
        cout << "Winner: Player White" << endl;
    } else if (sum_pieces < 0) {
        player1.add_status(-1);
        player2.add_status(1);
        cout << "Winner: Player Black" << endl;
    } else {
        player1.add_status(0);
        player2.add_status(0);
        cout << "The game ended in a tie" << endl;
    }
    is_game_ended = true;
}

void Reversi::test_win_condition(Client player1, Client player2) {
    bool first_has_moves = has_valid_moves();
    if (first_has_moves) {
        return;
    }
    current_player = -current_player;
    bool second_has_moves = has_valid_moves();
    if (!first_has_moves && !second_has_moves) {
        cout << "End of the game" << endl;
        ends_game(player1, player2);
    } else if (!first_has_moves && second_has_moves) {
        cout << (current_player == -1 ? player1.get_nickname() : player2.get_nickname()) << (current_player == 1 ? "(White)" : "(Black)") << " doesn't have valid moves. Switching players." << endl;
    }
}

void Reversi::play(Client player1, Client player2) {
    while (!is_game_ended) {
        print_board();
        test_win_condition(player1, player2);
        if (is_game_ended) {
            break;
        }
        read_move(player1, player2);
    }
}

bool Reversi::get_is_game_ended() {
    return is_game_ended;
}

int Reversi::get_current_player() {
    return current_player;
}

int Reversi::get_board(int x, int y) {
    if (x < 0 || x >= 8 || y < 0 || y >= 8) {
        throw std::invalid_argument("Coordinates must be between 0 and 7.");
    }
    return board[x][y];
}

Reversi::~Reversi() {}