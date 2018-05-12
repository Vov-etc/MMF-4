#ifndef LOBBY_H
#define LOBBY_H

#include <iostream>
#include <thread>
#include <map>
#include <ctime>
#include "buffer.h"
#include "ssocket.h"
using namespace std;

class player {
    int num;
    ssocket my_sock;
public:
    buffer in, out;
    player();
    void Accept(ssocket &listener);
    void Send();
    void Recv();

    int get_num();
    friend void sending(player &me);
    friend void recving(player &me);
};

class lobby {
    ssocket listener;
    thread listen;
    friend void accepting_clients(lobby &lobby);
    int new_player();
public:
    map<int, player> players;
    lobby();
    ~lobby();
    const map<int, player>& get_players() const;
    int num_of_players();
    void send_to(int num, string &str);
    void recv_from(int num);
};

#endif // !LOBBY_H
