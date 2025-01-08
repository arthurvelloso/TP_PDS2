#include <iostream>
using namespace std;

// Função para exibir o tabuleiro
void display(int Board[3][3]) {
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

// Função para verificar se há um vencedor
int checkWin(int Board[3][3]) {
    // Verifica linhas e colunas
    for (int i = 0; i < 3; i++) {
        int rowSum = Board[i][0] + Board[i][1] + Board[i][2];
        int colSum = Board[0][i] + Board[1][i] + Board[2][i];
        if (rowSum == 3 || colSum == 3) return 1;  // Jogador 1 venceu
        if (rowSum == -3 || colSum == -3) return -1; // Jogador 2 venceu
    }

    // Verifica diagonais
    int diag1 = Board[0][0] + Board[1][1] + Board[2][2];
    int diag2 = Board[0][2] + Board[1][1] + Board[2][0];
    if (diag1 == 3 || diag2 == 3) return 1;  // Jogador 1 venceu
    if (diag1 == -3 || diag2 == -3) return -1; // Jogador 2 venceu

    // Caso contrário, nenhum vencedor
    return 0;
}

bool isBoardFull(int Board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (Board[i][j] == 0) {
                return false; // Ainda há pelo menos uma casa vazia
            }
        }
    }
    return true; // Todas as casas estão preenchidas
}


// Função para atualizar o tabuleiro com a jogada do jogador
bool makeMove(int Board[3][3], int position, int player) {
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    if (Board[row][col] == 0) {
        Board[row][col] = player; // Atualiza com o valor do jogador
        return true;
    } else {
        cout << "POSIÇÃO OCUPADA, TENTE OUTRA" << endl;
        return false;
    }
}

int main() {
    int Board[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    int currentPlayer = 1; // Jogador inicial (1 = Jogador 1, -1 = Jogador 2)
    int position;
    int winner = 0;

    while (true) {
        display(Board);

        // Verifica se há vencedor
        winner = checkWin(Board);
        if (winner != 0) {
            cout << "Jogador " << (winner == 1 ? "1 (X)" : "2 (O)") << " venceu!" << endl;
            break;
        }

            // Verifica se deu velha (empate)
        if (isBoardFull(Board)) {
            cout << "VELHA" << endl;
            break;
        }  

        // Pede a jogada do jogador
        cout << "Jogador " << (currentPlayer == 1 ? "1 (X)" : "2 (O)") << ", escolha uma posição (1-9): ";
        cin >> position;
        cout << endl;

        if (position < 1 || position > 9) {
            cout << "Posição inválida! Escolha um número entre 1 e 9." << endl;
            continue;
        }

        if (makeMove(Board, position, currentPlayer)) {
            currentPlayer *= -1; // Alterna entre jogadores multiplicando por -1.
        }
    }

    return 0;
}
