#include <iostream>

using namespace std;

//declaracao dos metodos de Board (em board.hpp)
class Board {
private:


public:
    Board();

    virtual void print_board();
    virtual void read_move();
    virtual bool is_move_valid(int x);
    virtual void test_win_condition(int x);

    ~Board();
};


//declaracao dos metodos de Connect4 (em connect4.hpp)
class Connect4 : public Board {
private:
int board[6][7];
int column_height[6];
int current_player;
bool is_game_ended;

public:
    Connect4();
    void print_board() override;
    void read_move() override;
    bool is_move_valid(int x) override;
    void test_win_condition(int x) override;
    bool is_there_more_moves();
    void play();

};


//implementacao dos metodos Connect4 (em connect4.cpp)

//inicializador
Connect4::Connect4 () {
    for (int i = 0; i < 6; i++) {
        column_height[i] = 5;
        for (int j = 0; j < 7; j++) {
            board[i][j] = 0;
        }
    }

    current_player = 1;
    is_game_ended = false;
};



//imprimir o tabuleiro
void Connect4::print_board() {
    cout << " 0 1 2 3 4 5 6" << endl;
    for (int i = 0; i < 6; i++) {
        cout << i << " ";
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == 1) {
                cout << "B ";
            }
            else if (board[i][j] == -1) {
                cout << "W ";
            }
            else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}


//realizar jogada
void Connect4::read_move() {
    int move;
    bool valid_input = false;
    while (!valid_input) {
        cout << "It's " << (current_player == 1 ? "white" : "black") << "'s turn!" << endl;
        cout << "Enter the column you want to play (0-6)" << endl;
        cin >> move;
        if (is_move_valid(move)) {
            board[column_height[move]][move] = current_player;
            test_win_condition(move);   //checa se o jogador acabou de vencer
            column_height[move]--;
            current_player = -current_player;
            valid_input = true;
        }
        else {
            cout << "That's not a valid move! Enter a column between 0 and 6 that's not filled";
        }
    }
}


//testar se jogada é válida
bool Connect4::is_move_valid(int move) {
    if(0 <= move && move < 7 && column_height[move] > 0) {
        return true;
    }
    else {
        return false;
    }
}


//testar vitória
void Connect4::test_win_condition(int move) {
    int total = 1;
    for (int i = 0; i <= 1; i++) {
        for(int j = 0; j <= 1; j++) {
            int posx = column_height[move] + i;
            int posy = move + j;
            while (board[posx][posy] == current_player && posx >= 0 && posx < 7 && posy >=0 && posy < 6) {
                total++;
                posx += i;
                posy += j;
                if (total == 4) {
                    cout << (current_player == 1 ? "White" : "Black") << " player wins!" << endl;
                    is_game_ended = true;
                    return;
                }
            }
            posx = column_height[move] - i;
            posy = move - j;
            while (board[posx][posy] == current_player && posx >= 0 && posx < 7 && posy >=0 && posy < 6) {
                total++;
                posx -= i;
                posy -= j;
                if (total == 4) {
                    cout << (current_player == 1 ? "White" : "Black") << " player wins!" << endl;
                    is_game_ended = true;
                    return;
                }
            }
            total = 1;
        }
    }
}


//checar se o tabuleiro ta cheio
bool Connect4::is_there_more_moves() {
    int filled_columns = 0;
    for(int i = 0; i < 6; i++) {
        if (column_height[i] == 6) {
            filled_columns++;
        }
    }

    if(filled_columns == 6) {
        return false;
    }
    else {
        return true;
    }
}


//iniciar um jogo
void Connect4::play() {
    while (!is_game_ended) {
        print_board();
        read_move();
    }
    print_board();
}


int main() {

    Connect4 game;
    game.play();

    return 0;
}