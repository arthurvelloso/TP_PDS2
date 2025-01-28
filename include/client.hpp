#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>


class Client {
private:
    std::string nickname;
    std::string name;
    int victories;
    int ties;
    int defeats;


public:
    Client(std::string nick, std::string n, int d, int t, int v);

    bool search_client();
    void signup_client();
    void remove_client();
    void add_status(int n);
    std::string get_nickname();
    std::string get_name();
    int get_victories();
    int get_ties();
    int get_defeats();

    ~Client();
};


#endif //CLIENT_H