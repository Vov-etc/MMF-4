#include "includes/ssocket.h"

int ssocket::last_err = 0;
int ssocket::num = 0;

void ssocket::Startup() {
    if (_WIN32) {
        WSAData wsadata;
        last_err = WSAStartup(MAKEWORD(2, 2), &wsadata);
        if (last_err) {
            wcerr << "WSAStartup failed with code " << WSAGetLastError() << endl;
        } else {
            wcerr << "WSAStartup succeeded" << endl;
        }
    }
}
void ssocket::Cleanup() {
    if (_WIN32) {
        last_err = WSACleanup();
        if (last_err) {
            wcerr << "WSACleantup failed with code " << WSAGetLastError() << endl;
        } else {
            wcerr << "WSACleanup succeeded" << endl;
        }
    }
}

ssocket::ssocket() {
    if (num == 0) {
        Startup();
    }
    my_socket = INVALID_SOCKET;
    is_open = false;
    num++;
}
ssocket::ssocket(const ssocket &other) {
    if (num == 0) {
        Startup();
    }
    my_socket = INVALID_SOCKET;
    is_open = false;
    num++;
}
ssocket::~ssocket() {
    num--;
    Close();
    if (num == 0) {
        Cleanup();
    }
}

SOCKET ssocket::get_socket() const {
    return my_socket;
}
void ssocket::Close() {
    if (is_open) {
        last_err = closesocket(my_socket);
        if (last_err) {
            wcerr << my_socket << " closing socket failed with code " << WSAGetLastError() << endl;
        } else {
            wcerr << my_socket << " closing socket succeeded" << endl;
        }
        is_open = false;
    }
}
void ssocket::Swap(ssocket &other) {
    SOCKET swap_socket = my_socket;
    bool swap_is_open = is_open;
    my_socket = other.my_socket;
    other.my_socket = swap_socket;
    other.is_open = swap_is_open;
}

void ssocket::Bind(string my_port) {
    addrinfo hints, *my_addr;
    BOOL bOptVal = FALSE;
    int bOptLen = sizeof(BOOL);

    ZeroMemory(&hints, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, my_port.c_str(), &hints, &my_addr);

    my_socket = socket(my_addr->ai_family, my_addr->ai_socktype, my_addr->ai_protocol);
    if (my_socket == INVALID_SOCKET) {
        is_open = false;
        wcerr << "/n" << my_socket << " socket function failed with code " << WSAGetLastError() << endl;
    } else {
        is_open = true;
        wcerr << my_socket << " socket function succeeded" << endl;
    }

    last_err = setsockopt(my_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&bOptVal, bOptLen);
    if (last_err) {
        wcerr << my_socket << " setsockopt() failed with code " << WSAGetLastError() << endl;
    }

    last_err = bind(my_socket, my_addr->ai_addr, my_addr->ai_addrlen);
    if (last_err) {
        wcerr << my_socket << " binding socket failed with code " << WSAGetLastError() << endl;
    } else {
        wcerr << my_socket << " binding socket succeeded" << endl;
    }
    freeaddrinfo(my_addr);
}
void ssocket::Connect(string target_in_addr, string target_port) {
    addrinfo hints, *target_addr;

    ZeroMemory(&hints, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    last_err = getaddrinfo(target_in_addr.c_str(), target_port.c_str(), &hints, &target_addr);
    if (last_err) {
        wcerr << my_socket << " getaddrinfo() failed with code " << WSAGetLastError() << endl;
    }

    my_socket = socket(target_addr->ai_family, target_addr->ai_socktype, target_addr->ai_protocol);
    if (my_socket == INVALID_SOCKET) {
        wcerr << "/n" << my_socket << " socket function failed with code " << WSAGetLastError() << endl;
    } else {
        wcerr << my_socket << " socket function succeeded" << endl;
    }

    last_err = connect(my_socket, target_addr->ai_addr, target_addr->ai_addrlen);
    if (last_err) {
        is_open = false;
        wcerr << my_socket << " connection failed with code " << WSAGetLastError() << endl;
    } else {
        is_open = true;
        wcerr << my_socket << " connection succeeded" << endl;
    }
    freeaddrinfo(target_addr);
}
void ssocket::Listen(int vol) {
    last_err = listen(my_socket, vol);
    if (last_err) {
        wcerr << my_socket << " listening failed with code " << WSAGetLastError() << endl;
    } else {
        wcerr << my_socket << " listening started" << endl;
    }
}
void ssocket::Accept(const ssocket &listener) {
    my_socket = accept(listener.get_socket(), NULL, NULL); //TODO
    if (my_socket == INVALID_SOCKET) {
        is_open = false;
        wcerr << my_socket << " acception failed with code " << WSAGetLastError() << endl;
    } else {
        is_open = true;
        wcerr << my_socket << " acception succeeded" << endl;
    }
}

bool ssocket::Is_Open() {
    return is_open;
}

int ssocket::Send(char* c_data, int len) {
    int sended = 0;
    c_data[2];
    while (sended != len) {
        int temp = 0;
        temp = send(my_socket, c_data, len, 0);
        if (temp < 0) {
            wcout << WSAGetLastError() << endl;
            Close();
            return -1;
        }
        sended += temp;
    }
    return sended;
}
int ssocket::Recv(char* c_data, int len) {
    int recved = recv(my_socket, c_data, len, 0);
    if (recved < 0) {
        Close();
        return -1;
    }
    return recved;
}

/*void ssocket::send_buff(buffer &buff) {
    int len = buff.Size();
    Send((char*)&len, sizeof(int) / sizeof(char));
    buff.lock();
    Send(buff.Data(), buff.Size());
    buff.unlock();
}
void ssocket::recv_buff(buffer &buff) {
    int len = -1;
    Recv((char*)&len, sizeof(int) / sizeof(char));
    buff.lock();
    buff.resize(len);
    Recv(buff.Data(), buff.Size());
    buff.unlock();
}*/
