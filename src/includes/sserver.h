#ifndef SERVER_H
#define SERVER_H

#include <thread>
#include <map>
#include "ssocket.h"
using namespace std;

class sserver {
    ssocket listener;
    thread listen;
    map<int, ssocket> clients;
public:
    sserver();
    ~sserver();
    int num_of_clients() {
        return clients.size();
    }
    template <typename T>
    void send_to(int a, vector<T> &data) {
        clients[a].Send(data);
    }
    friend void accepting_clients(sserver &serv);
};

#endif // !SERVER_H
