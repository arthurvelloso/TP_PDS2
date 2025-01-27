#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>


//user TAD and methods
class Client {
private:

    std::string name;
    std::string nickname;
    int score;
    int victoryCount;
    int tieCount;
    int defeatCount;


public:
    Client(std::string name, std::string nickname);

    void signup_client();
    void remove_client();
    void print_client_list();
    void add_victory();
    void add_defeat();
    void add_tie();

    ~Client();
};


#endif //CLIENT_H