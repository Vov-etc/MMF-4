#ifndef SOCKET_TCP_H
#define SOCKET_TCP_H


#pragma comment(lib,"Ws2_32.lib")

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#include "ssocket_define.h"

using namespace std;

class ssocket {
    static int last_err;
    static int num;
    SOCKET my_socket;
    sockaddr_in my_addr;

    static void Start();
    static void Close();
public:
    ssocket();
    ~ssocket();

    static int get_last_error() {
        return last_err;
    }
    SOCKET get_socket() {
        return my_socket;
    }

    void swap(ssocket &other);
    void Bind(short my_port = PORT);
    void Connect(string target_in_addr = SERVERADDR, short target_port = PORT);
    void Listen(int vol = 5);
    void Accept(ssocket &listener);
    template <typename T>
    void Send(vector<T> &data) {
        int len = data.size() * sizeof(T) / sizeof(char);
        send(my_socket, (char*)&len, sizeof(int) / sizeof(char), 0);
        if (len > 0) { 
            send(my_socket, (char*)data.data(), len, 0);
        }
    }
    template <typename T>
    void Recv(vector<T> &data) {
        int len;
        recv(my_socket, (char*)&len, sizeof(int) / sizeof(char), 0);
        data.resize(len * sizeof(char) / sizeof(T));
        if (len > 0) {
            recv(my_socket, (char*)&data[0], len, 0);
        }
    }
};

#endif // !SOCKET_TCP_H
