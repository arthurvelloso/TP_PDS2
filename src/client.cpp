#include <iostream>
#include <fstream>
#define FILE_NAME "users/users.txt"
#define TEMP_NAME "users/temp.txt"


bool search_client(std::string nick) {
    std::ifstream userFile(FILE_NAME);
    std::string search;
    std::string comp = "Nickname: ";
    comp.append(nick);

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



void signup_client() {
    std::ofstream userFile(FILE_NAME);


    std::string n, nick;
    std::cout << "Enter your first name: ";
    std::cin >> n;
    std::cout << "Enter your nickname: ";
    std::cin >> nick;


    while( search_client(nick) ) {
        std::cout << "This nickname already exists. Enter another one: ";
        std::cin >> nick;
    }


    userFile << "User" << std::endl;
    userFile << "Nickname: " << nick << std::endl;
    userFile << "Name: " << n << std::endl;
    userFile << "Victory: 0" << std::endl << "Tie: 0" << std::endl << "Defeat: 0" << std::endl;
    userFile << std::endl << std::endl << std::endl;

    userFile.close();
}



void remove_client() {
    std::fstream userFile(FILE_NAME);
    std::string nick;
    std::string deleteLine = "Nickname: ";
    deleteLine.append(nick);
    std::string line;


    std::cout << "What user do you want to delete? ";
    std::cin >> nick;


    if ( !search_client(nick) ) {
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



void print_client_list() {
    std::fstream userFile(FILE_NAME);
    std::string line;

    while ( getline(userFile, line) ) {
        std::cout << line << std::endl;
    }
    userFile.close();
}



void add_victory(std::string nick) {
    std::ifstream userFile(FILE_NAME);
    std::string line;
    std::string comp = "Nickname: ";
    comp.append(nick);

    std::ofstream temp;
    temp.open(TEMP_NAME);

    do {
        getline(userFile, line);
        temp << line << std::endl;
    } while(line != comp);


    getline(userFile, line);
    int n;
    userFile >> line >> n;
    n++;
    temp << line << " " << n << std::endl;

    while ( getline(userFile, line) ) {
        temp << line << std::endl;
    }
    

    userFile.close();
    temp.close();
    remove(FILE_NAME);
    rename(TEMP_NAME, FILE_NAME);
}



void add_tie(std::string nick) {
    std::ifstream userFile(FILE_NAME);
    std::string line;
    std::string comp = "Nickname: ";
    comp.append(nick);

    std::ofstream temp;
    temp.open(TEMP_NAME);

    do {
        getline(userFile, line);
        temp << line << std::endl;
    } while(line != comp);


    getline(userFile, line);
    getline(userFile, line);
    int n;
    userFile >> line >> n;
    n++;
    temp << line << " " << n << std::endl;

    while ( getline(userFile, line) ) {
        temp << line << std::endl;
    }
    

    userFile.close();
    temp.close();
    remove(FILE_NAME);
    rename(TEMP_NAME, FILE_NAME);
}



void add_defeat(std::string nick) {
    std::ifstream userFile(FILE_NAME);
    std::string line;
    std::string comp = "Nickname: ";
    comp.append(nick);

    std::ofstream temp;
    temp.open(TEMP_NAME);

    do {
        getline(userFile, line);
        temp << line << std::endl;
    } while(line != comp);


    getline(userFile, line);
    getline(userFile, line);
    getline(userFile, line);
    int n;
    userFile >> line >> n;
    n++;
    temp << line << " " << n << std::endl;

    while ( getline(userFile, line) ) {
        temp << line << std::endl;
    }
    

    userFile.close();
    temp.close();
    remove(FILE_NAME);
    rename(TEMP_NAME, FILE_NAME);
}