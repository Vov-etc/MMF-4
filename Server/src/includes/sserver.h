#ifndef SSERVER_H
#define SSERVER_H

#include "ssocket.h"
#include <thread>
#include <map>
using namespace std;

template <typename T>
void to_buff(vector<T> &data, char* &c_data, int &len) {
    len = data.size() * sizeof(T) / sizeof(char);
    c_data = (char *)data.data();
}

class sserver {
    ssocket listener;
    thread listen;
public:
    map<int, ssocket> clients;
    sserver();

    int num_of_clients() {
        return clients.size();
    }
    template <typename T>
    void send_to(int a, vector<T> &data) {
        char* c_data = NULL;
        int len = 0;
        to_buff(data, c_data, len);
        if (len > 0) {
            clients[a].Send(c_data, len);
        }
    }
    friend void accepting_clients(sserver &serv);
};

#endif // !SSERVER_H
