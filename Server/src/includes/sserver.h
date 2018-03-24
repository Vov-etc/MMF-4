#ifndef SSERVER_H
#define SSERVER_H

#include "ssocket.h"
#include <thread>
#include <map>
using namespace std;


class client {
    thread send, recv;
public:
    ssocket socket;
    buffer *in, out;
    client();
    client(buffer &_in, ssocket &new_socket);
    client::client(client &other);

    friend void sending(client &me);
    friend void recving(client &me);
};

class sserver {
    ssocket listener;
    thread listen;
    buffer recved;
public:
    map<int, client> clients;
    sserver();

    int num_of_clients();

    template <typename T>
    void send_to(int a, vector<T> &data) {
        char* c_data = NULL;
        int len = 0;
        if (len > 0) {
            clients[a].out.vtobuff(data);
        }
    }
    /*template <typename T>
    void send_to(int a, vector<T> &data) {
        char* c_data = NULL;
        int len = 0;
        to_buff(data, c_data, len);
        if (len > 0) {
            clients[a].Send(c_data, len);
        }
    }*/
    friend void accepting_clients(sserver &serv);
};

#endif // !SSERVER_H
