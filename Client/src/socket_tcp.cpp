#include "includes/socket_tcp.h"

int ssocket::last_err = 0;
int ssocket::num = 0;

void ssocket::Start() {
    if (_WIN32) {
        WSAData wsadata;
        last_err = WSAStartup(MAKEWORD(2, 2), &wsadata);
        if (last_err) {
            cerr << "WSAStartup failed with code " << last_err << endl;
        } else {
            cerr << "WSAStartup succeeded" << endl;
        }
    }
}

void ssocket::Close() {
    if (_WIN32) {
        last_err = WSACleanup();
        if (last_err) {
            cerr << "WSACleantup failed with code " << last_err << endl;
        } else {
            cerr << "WSACleanup succeeded" << endl;
        }
    }
}

ssocket::ssocket() {
    id = num;
    if (num == 0) {
        Start();
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        cerr << "socket function failed with error = " << errno << endl;
    } else {
        cerr << "socket function succeeded" << endl;
    }
    num++;
}

ssocket::~ssocket() {
    num--;
    last_err = closesocket(sock);
    if (num == 0) {
        Close();
    }
}

void ssocket::Bind(short my_port) {
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(my_port);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, NULL, 0);

    last_err = bind(sock, (sockaddr*)&my_addr, sizeof(my_addr));
    if (last_err) {
        cerr << "binding socket failed with code" << last_err << endl;
    } else {
        cerr << "binding socket succeeded" << endl;
    }
}

void ssocket::Connect(short port, string target_in_addr) {
    sockaddr_in target_addr;
    memset((char *)&target_addr, 0, sizeof(target_addr));
    target_addr.sin_family = AF_INET;
    target_addr.sin_port = htons(PORT);
    last_err == inet_pton(AF_INET, target_in_addr.c_str(), &target_addr.sin_addr);
    last_err = connect(sock, (sockaddr *)&target_addr, sizeof(target_addr));
    if (last_err) {
        cerr << "connection failed with code " << last_err << endl;
    } else {
        cerr << "connection succeeded" << endl;
    }
}

void ssocket::Listen(int vol) {
    listen(sock, vol);
    cerr << "listening started" << endl;
}

void ssocket::Accept(ssocket listener) {
    sock = accept(listener.get_socket(), (sockaddr*)&my_addr, NULL);
    if (sock == INVALID_SOCKET) {
        cerr << "acception failed with error = " << errno << endl;
    } else {
        cerr << "acception succeeded" << endl;
    }
}