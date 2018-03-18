#include "includes/sserver.h"

void accepting_clients(sserver &serv) {
    while (true) {
        serv.clients[serv.clients.size()].Accept(serv.listener);
    }
}

sserver::sserver() {
    listener.Bind();
    listener.Listen();
    listen = thread(accepting_clients, ref(*this));
}

sserver::~sserver() {
    listen.join();
}