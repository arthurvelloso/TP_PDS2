#include <iostream>

using namespace std;

//declaracao dos metodos de Board (em board.hpp)
class Board {
private:


public:
    Board();

    virtual void print_board();
    virtual void read_move();
    virtual bool is_move_valid(int x, int y);
    virtual void test_win_condition();

    ~Board();
};


//declaracao dos metodos de Reversi (em reversi.hpp)
class Reversi : public Board {
private:
    int current_player;
    int board[8][8];
    bool is_game_ended;

public:
    Reversi();
    void print_board() override;
    void read_move() override;
    bool is_move_valid(int x, int y) override;
    bool has_valid_moves();
    void test_win_condition() override;
    void ends_game();
    void play();
    ~Reversi();
};

//implementacao dos metodos Board (em board.cpp)
Board::Board() {}

void Board::print_board() {}

void Board::read_move() {}

bool Board::is_move_valid(int x, int y) { return false; }

void Board::test_win_condition() {}

Board::~Board() {}

//implementacao dos metodos Reversi (em reversi.cpp)

//inicializa tabuleiro e variaveis
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

//verifica se jogada e valida
bool Reversi::is_move_valid(int x, int y){
    if (x >= 0 && x < 8 && y >= 0 && y < 8 && board[x][y] == 0){
        for(int i = -1; i <= 1; i++){
            for(int j = -1; j <= 1; j++){
                int posx = x + i;
                int posy = y + j;
                while(posx >= 0 && posx < 8 && posy >= 0 && posy < 8 && board[posx][posy] == -current_player){
                    posx = posx + i;
                    posy = posy + j;
                    if(board[posx][posy] == current_player){
                        return true;
                    }
                }
            }
        }
    }
        return false;
}

//imprime tabuleiro
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

//le jogada
void Reversi::read_move() {
    int x, y;
    bool valid_input = false;
    while (!valid_input) {
        cout << "Player " << (current_player == 1 ? "White" : "Black") << "'s turn" << endl;
        cout << "Enter row (0-7) and column (0-7) separated by space: ";
        cin >> x >> y;
        //FALTA: criar mais validação para garantir que input é válido
        if (is_move_valid(x, y)) {
            board[x][y] = current_player;
            for(int i = -1; i <= 1; i++) {
                for(int j = -1; j <= 1; j++) {
                    int posx = x + i;
                    int posy = y + j;
                    while(board[posx][posy] == -current_player && posx >= 0 && posx < 8 && posy >= 0 && posy < 8){
                        posx += i;
                        posy += j;
                        if(board[posx][posy] == current_player){
                            posx = x + i;
                            posy = y + j;
                            while(board[posx][posy] == -current_player){
                                board[posx][posy] = current_player;
                                posx += i;
                                posy += j;
                            }
                        }
                    }
                }
            }
            current_player = -current_player;
            valid_input = true;
        }
        else{
            cout << "Invalid move! Try again" << endl;
        }
    }
}

//verifica se current_player possui jogadas validas
bool Reversi::has_valid_moves(){
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
                if(is_move_valid(i, j)){
                    return true;
                }
        }
    }
    return false;
}

//finaliza o jogo
void Reversi::ends_game(){
    int sum_pieces = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
                sum_pieces = sum_pieces + board[i][j];
        }
    }
    if(sum_pieces > 0){
        cout << "Winner: Player White" << endl;
    }
    else if(sum_pieces < 0){
        cout << "Winner: Player Black" << endl;
    }
    else{
        cout << "The game ended with a tie" << endl;
    }
    is_game_ended = true;

}

//testa condicao de vitoria
void Reversi::test_win_condition() {
    bool first_has_moves = has_valid_moves();
    if(first_has_moves == true){
        return;
    }
    current_player = -current_player;
    bool second_has_moves = has_valid_moves();
    if(first_has_moves == false && second_has_moves == false){
        cout << "End of the game" << endl;
        ends_game();
    }
    else if(first_has_moves == false && second_has_moves == true){
        cout << "Player " << (current_player == -1 ? "White" : "Black") << " doesn't have valid moves. Switching players." << endl;
    }
}

//inicia uma partida
void Reversi::play(){
    while(is_game_ended == false){
        print_board();
        test_win_condition();
        if(is_game_ended == true){
            break;
        }
        read_move();
    }
}

Reversi::~Reversi() {}


int main(){

    Reversi game;
    game.play();


    return 0;
}