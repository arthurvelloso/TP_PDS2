#include <iostream>
#include <vector>

#include <limits>
#include <stdexcept>

#include <fstream>
#define FILE_NAME "users/users.txt"

#include "board.hpp"
#include "client.hpp"
#include "tictactoe.hpp"
#include "reversi.hpp"
#include "connect4.hpp"

using namespace std;

// Instanciando todos os jogadores já registrados no .txt
void instance_all(vector<Client>& clients) {  
    ifstream userFile(FILE_NAME);
    string line;
    string nick;
    string n;
    int d, t, v;

    if ( userFile.is_open() ) {
        while ( getline(userFile, line) ) {
            if (line == "User") {
                userFile >> line >> nick >> line >> n >> line >> d >> line >> t >> line >> v;
                clients.push_back(Client(nick, n, d, t, v));
            }
        }
    }
}

void sign_up_player(vector<Client>& clients) {
    try {
        string nickname;
        cout << "Enter your nickname: ";
        cin >> nickname;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Invalid entry! Please, enter a valid nickname.");
        }

        // Verificação em vector de Players
        for (Client& player : clients) {
            if (player.get_nickname() == nickname) {
                throw runtime_error("That nickname already exists. Choose another nickname.");
            }
        }    
        // Criação direta do objeto Player e inserção no vector
        
        string name;
        cout << "Enter your first name: " << endl;
        cin >> name;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Invalid entry! Please, enter a valid nickname.");
        }

        clients.push_back(Client(nickname, name, 0, 0, 0));
        clients.back().signup_client();
        cout << "Player register successfully!" << endl;
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    } catch (const runtime_error& e) {
        cerr << "Registry error: " << e.what() << endl;
    } catch (const exception& e) {
        cerr << "Unexpected error: " << e.what() << endl;
    }
}

void remove_player(vector <Client>& clients) {
    cout << "Type the nickname of the player you want to remove: ";

    try {
        string nick;
        int flag = 0;
        
        cin >> nick;
        for (Client& player : clients) {
            if (player.get_nickname() == nick) {
                player.remove_client();
                clients.clear();
                instance_all(clients);
                flag = 1;
            break;
            }
        }
        
        if(flag == 0) {
            throw std::invalid_argument("OCCUPED POSITION, TRY AGAIN");
        }
    }
    catch(const std::invalid_argument& e) {
        cout << e.what() << endl;
    }
}


void list_players(vector<Client> clients) {
    for (Client& c : clients) {
        cout << "Nickname: " << c.get_nickname() << endl;
        cout << "Name: " << c.get_name() << endl;
        cout << "Victories: " << c.get_victories() << endl;
        cout << "Ties: " << c.get_ties() << endl;
        cout << "Defeats " << c.get_defeats() << endl << endl;
    }
}

void execute_game(vector<Client> clients) {
cout << "Enter the game you want to play: " << endl;
    cout << "TicTacToe (T)    Reversi (R)     Connect4 (C)" << endl;
    char command;
    try {
        cin >> command;
        int p1_index = 0, p2_index = 0;

        // Validação do comando
        if (command != 'T' && command != 'R' && command != 'C') {
            throw invalid_argument("Invalid argument. You must enter 'T', 'R', or 'C'. Try again.");
        }

        cout << "Enter the player 1 nickname: " << endl;
        string player1;
        cin >> player1;

        // Verifica se o jogador 1 existe
        p1_index = -1;
        for (unsigned int i = 0; i < clients.size(); ++i) {
            if (clients[i].get_nickname() == player1) {
                p1_index = i;
                break;
            }
        }
        if (p1_index == -1) {
            throw invalid_argument("Player 1 not found. Please enter a valid nickname.");
        }

        cout << "Enter the player 2 nickname: " << endl;
        string player2;
        cin >> player2;

        // Verifica se o jogador 2 existe
        p2_index = -1;
        for (unsigned int i = 0; i < clients.size(); ++i) {
            if (clients[i].get_nickname() == player2) {
                p2_index = i;
                break;
            }
        }
        if (p2_index == -1) {
            throw invalid_argument("Player 2 not found. Please enter a valid nickname.");
        }

        // Inicia o jogo correspondente
        if (command == 'R') {
            Reversi game;
            game.play(clients[p1_index], clients[p2_index]);
        } else if (command == 'C') {
            Connect4 game;
            game.play(clients[p1_index], clients[p2_index]);
        } else if (command == 'T') {
            Tictactoe game;
            game.play(clients[p1_index], clients[p2_index]);
        }
    }
    catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }
}

int main(){
    string command;

    vector<Client> clients;
    instance_all(clients);
    cout << "Welcome! We're happy to have you here!" << endl;

    while (true) {
        cout << "Type what you want to do: "  << endl;
        cout << "Sign up player: ( SP )      Remove player: ( RP )" << endl;
        cout << "List players:   ( LP )      Execute game:  ( EG )" << endl;
        cout << "End the system: ( END )" << endl;
        
        cin >> command;

        // Converte comando para maiúsculas para evitar erros
        for (char &c : command) {
            c = toupper(c);
        }

        try {
            if (command == "SP") {
                sign_up_player(clients);
            } else if (command == "RP") {
                remove_player(clients);
            } else if (command == "LP") {
                list_players(clients);
            } else if (command == "EG") {
                execute_game(clients);
                clients.clear();
                instance_all(clients);
            } else if (command == "END") {
                cout << ":( System shutting down. Goodbye!" << endl;
                break;
            } else {
                throw invalid_argument("Invalid input! Please type a valid command.");
            }
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
        }

        cout << endl; // Espaçamento para melhorar a legibilidade
    }

    return 0;
}
