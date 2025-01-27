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

vector<Client> clients;

// Instanciando todos os jogadores já registrados no .txt
void instance_all(vector<Client> clients) {
    ifstream userFile(FILE_NAME);
    string line;
    string nick;
    string n;
    int d, t, v;

    while ( !userFile.eof() ) {
        while ( line != "User" ) {
            userFile >> line;
        }

        userFile >> line >> nick >> line >> n >> line >> d >> line >> t >> line >> v;
        clients.push_back(Client(nick, n, d, t, v));
    }
}

void sign_up_player() {
    try {
        string nickname;
        cout << "Enter your nickname: ";
        cin >> nickname;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Entrada inválida! Por favor, insira um nickname válido.");
        }

        // Verificação em vector de Players
        for (const Client& player : clients) {
            if (player.get_nickname() == nickname) {
                throw runtime_error("That nickname already exists. Choose another nickname.");
            }
    
        // Criação direta do objeto Player e inserção no vector
        
        string name;
        cout << "Enter your name: " << endl;
        cin >> name;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Entrada inválida! Por favor, insira um nickname válido.");
        }

        clients.push_back(Client(nickname, name, 0, 0, 0));
        cout << "Player register successfully!" << endl;

    } catch (const invalid_argument& e) {
        cerr << "Erro de entrada: " << e.what() << endl;
        throw;
    } catch (const runtime_error& e) {
        cerr << "Erro de registro: " << e.what() << endl;
        throw;
    } catch (const exception& e) {
        cerr << "Erro inesperado: " << e.what() << endl;
        throw;
    }
}




void instance_all(clients);


int main(){
    string command;

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
                sign_up_player();
            } else if (command == "RP") {
                remove_player();
            } else if (command == "LP") {
                list_players();
            } else if (command == "EG") {
                execute_game();
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