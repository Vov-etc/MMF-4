#ifndef SSOCKET_H
#define SSOCKET_H

#ifdef _WIN32
#pragma comment (lib, "ws2_32.lib")

#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define WSAGetLastError() errno
typedef int SOCKET;
#endif
#include "buffer.h"
using namespace std;

#define SERVERADDR "127.0.0.1"
#define PORT "5050"


class ssocket {
    static int last_err;
    static int num;
    SOCKET my_socket;
    bool is_open;

    static void Startup();
    static void Cleanup();
public:
    ssocket();
    ssocket(const ssocket &other);
    ~ssocket();

    SOCKET get_socket() const;
    void Close();
    void Swap(ssocket &other);

    void Bind(string my_port = PORT);
    void Connect(string target_in_addr = SERVERADDR, string target_port = PORT);
    void Listen(int vol = 5);
    void Accept(const ssocket &listener);

    int Send(char* c_data, int len);
    int Recv(char* c_data, int len);
    void send_buff(buffer &buff);
    void recv_buff(buffer &buff);

    /*template <typename T>
    int Recv(vector<T> &data) {
        int len;
        last_err = recv(my_socket, (char*)&len, sizeof(int) / sizeof(char), 0);
        if(last_err < 0) {
            Close();
            return -1;
        }
        data.resize(len * sizeof(char) / sizeof(T));
        if (len > 0) {
            last_err = recv(my_socket, (char*)&data[0], len, 0);
            if (last_err < 0) {
                Close();
                return -1;
            }
        }
        return len;
    }*/

};

#endif // !SSOCKET_H
