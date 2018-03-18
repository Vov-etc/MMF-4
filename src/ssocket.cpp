#include "includes/ssocket.h"

int ssocket::last_err = 0;
int ssocket::num = 0;

void ssocket::Start() {
    if (_WIN32) {
        WSAData wsadata;
        last_err = WSAStartup(MAKEWORD(2, 2), &wsadata);
        if (last_err) {
            wcerr << "WSAStartup failed with code " << last_err << endl;
        } else {
            wcerr << "WSAStartup succeeded" << endl;
        }
    }
}

void ssocket::Close() {
    if (_WIN32) {
        last_err = WSACleanup();
        if (last_err) {
            wcerr << "WSACleantup failed with code " << last_err << endl;
        } else {
            wcerr << "WSACleanup succeeded" << endl;
        }
    }
}

ssocket::ssocket() {
    if (num == 0) {
        Start();
    }
    my_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (my_socket == INVALID_SOCKET) {
        wcerr << "/n" << my_socket << " socket function failed with code " << errno << endl;
    } else {
        wcerr << my_socket << " socket function succeeded" << endl;
    }
    num++;
}

ssocket::~ssocket() {
    num--;
    last_err = closesocket(my_socket);
    if (last_err) {
        wcerr << my_socket << " closing socket failed with code " << last_err << endl;
    } else {
        wcerr << my_socket << " closing socket succeeded" << endl;
    }
    if (num == 0) {
        Close();
    }
    wcerr << my_socket << " destruction socket succeeded\n" << endl;
}

void ssocket::swap(ssocket &other) {
    sockaddr_in swap_addr = my_addr;
    SOCKET swap_socket = my_socket;
    my_addr = other.my_addr;
    my_socket = other.my_socket;
    other.my_addr = swap_addr;
    other.my_socket = swap_socket;
}

void ssocket::Bind(short my_port) {
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(my_port);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    last_err = setsockopt(my_socket, SOL_SOCKET, SO_REUSEADDR, NULL, 0);
    if (last_err) {
        wcerr << my_socket << " setsockopt() failed with code " << last_err << endl;
    }

    last_err = bind(my_socket, (sockaddr*)&my_addr, sizeof(my_addr));
    if (last_err) {
        wcerr << my_socket << " binding socket failed with code " << last_err << endl;
    } else {
        wcerr << my_socket << " binding socket succeeded" << endl;
    }
}

void ssocket::Connect(string target_in_addr, short port) {
    sockaddr_in target_addr;
    memset((char *)&target_addr, 0, sizeof(target_addr));
    target_addr.sin_family = AF_INET;
    target_addr.sin_port = htons(PORT);
    last_err = inet_pton(AF_INET, target_in_addr.c_str(), &target_addr.sin_addr);
    if (last_err) {
        wcerr << my_socket << " inet_pton() failed with code " << last_err << endl;
    }
    last_err = connect(my_socket, (sockaddr *)&target_addr, sizeof(target_addr));
    if (last_err) {
        wcerr << my_socket << " connection failed with code " << last_err << endl;
    } else {
        wcerr << my_socket << " connection succeeded" << endl;
    }
}

void ssocket::Listen(int vol) {
    last_err = listen(my_socket, vol);
    if (last_err) {
        wcerr << my_socket << " listening failed with code " << last_err << endl;
    } else {
        wcerr << my_socket << " listening started" << endl;
    }
}

void ssocket::Accept(ssocket &listener) {
    last_err = closesocket(my_socket);
    if (last_err) {
        wcerr << my_socket << " closing socket failed with code " << last_err << endl;
    } else {
        wcerr << my_socket << " closing socket succeeded" << endl;
    }
    my_socket = accept(listener.get_socket(), (sockaddr*)&my_addr, NULL);
    if (my_socket == INVALID_SOCKET) {
        wcerr << my_socket << " acception failed with code " << errno << endl;
    } else {
        wcerr << my_socket << " acception succeeded" << endl;
    }
}