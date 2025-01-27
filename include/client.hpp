#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>


class Client {
public:
    bool search_client(std::string nick);
    void signup_client();
    void remove_client();
    void print_client_list();
    void add_victory(std::string nick);
    void add_defeat(std::string nick);
    void add_tie(std::string nick);
};


#endif //CLIENT_H