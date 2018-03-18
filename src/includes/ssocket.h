#ifndef SOCKET_TCP_H
#define SOCKET_TCP_H


#pragma comment(lib,"Ws2_32.lib")

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "ssocket_define.h"

using namespace std;

class ssocket {
    static int last_err;
    static int num;
    SOCKET my_socket;
    sockaddr_in my_addr;
    int id;

    static void Start();
    static void Close();
public:
    ssocket();
    ~ssocket();

    SOCKET get_socket() {
        return my_socket;
    }

    void Bind(short my_port = PORT);
    void Connect(short target_port = PORT, string target_in_addr = SERVERADDR);
    void Listen(int vol = 5);
    void Accept(ssocket listener);
};

#endif // !SOCKET_TCP_H
