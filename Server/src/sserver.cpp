#include "includes/sserver.h"

void accepting_clients(sserver &serv) {
    while (true) {
        ssocket new_socket;
        new_socket.Accept(serv.listener);
        serv.clients[serv.clients.size()].Swap(new_socket);
    }
}

sserver::sserver() {
    listener.Bind();
    listener.Listen();
    listen = thread(accepting_clients, ref(*this));
    listen.detach();
}