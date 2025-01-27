#include <iostream>
#include "board.hpp"
#include "client.hpp"
#include "tictactoe.hpp"
#include "reversi.hpp"
#include "connect4.hpp"

using namespace std;

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

        cout << endl;
    }

    return 0;
}
