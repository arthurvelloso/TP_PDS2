#include "client.hpp"
#include <iostream>
#include <fstream>
#define FILE_NAME "users/users.txt"
#define TEMP_NAME "users/temp.txt"


Client::Client() {
    nickname = "John";
    name = "Doe";
    defeats = ties = victories = 0;
}


Client::Client (std::string nick, std::string n, int d, int t, int v) {
    nickname = nick;
    name = n;
    defeats = d;
    ties = t;
    victories = v;
}


bool Client::search_client() {
    std::ifstream userFile(FILE_NAME);
    std::string search;
    std::string comp = "Nickname: ";
    comp.append(nickname);

    while ( !userFile.eof() ) {
        getline(userFile, search);

        if ( search == comp ) {
            userFile.close();
            return true;
        }
    }

    userFile.close();
    return false;
}



void Client::signup_client() {
    std::ofstream userFile(FILE_NAME);


    userFile << "User" << std::endl;
    userFile << "Nickname: " << nickname << std::endl;
    userFile << "Name: " << name << std::endl;
    userFile << "Defeats: 0" << std::endl << "Ties: 0" << std::endl << "Victories: 0" << std::endl;
    userFile << std::endl << std::endl << std::endl;

    userFile.close();
}


std::string Client::get_nickname() {
    return nickname;
}
std::string Client::get_name() {
    return name;
}
int Client::get_victories() {
    return victories;
}
int Client::get_ties() {
    return ties;
}
int Client::get_defeats() {
    return defeats;
}


void Client::remove_client() {
    std::fstream userFile(FILE_NAME);
    std::string deleteLine = "Nickname: ";
    deleteLine.append(nickname);
    std::string line;


    if ( !this->search_client() ) {
        std::cout << "This user does not exist" << std::endl;
        userFile.close();
        return;
    }
    

    std::ofstream temp;
    temp.open(TEMP_NAME);

    while ( getline(userFile, line) ) {
        if(line != deleteLine) {
            temp << line << std::endl;
        }
        else {
            while( !userFile.eof() && line != "User") {
                getline(userFile, line);
            }
        }
    }
    
    userFile.close();
    temp.close();
    remove(FILE_NAME);
    rename(TEMP_NAME, FILE_NAME);
}



void Client::add_status(int n) {
    std::ifstream userFile(FILE_NAME);
    std::string line;
    std::string comp = "Nickname: ";
    comp.append(nickname);

    std::ofstream temp;
    temp.open(TEMP_NAME);

    do {
        getline(userFile, line);
        temp << line << std::endl;
    } while(line != comp);


    //aqui é decidido se vai adicionar vitória, empate ou derrota
    n += 2;
    for ( int i = 0; i < n; i++ ) {
        getline(userFile, line);
        temp << line << std::endl;
    }
    
    getline(userFile, line);
    if ( n == 1 ) {
        defeats++;
        temp << "Defeats: " << defeats << std::endl;
    }
    else if ( n == 2 ) {
        ties++;
        temp << "Ties: " << ties << std::endl;
    }
    else {
        victories++;
        temp << "Victories: " << victories << std::endl;
    }


    while ( getline(userFile, line) ) {
        temp << line << std::endl;
    }
    

    userFile.close();
    temp.close();
    remove(FILE_NAME);
    rename(TEMP_NAME, FILE_NAME);
}


Client::~Client(){}