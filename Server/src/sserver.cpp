#include "includes/sserver.h"

client::client() {
    socket;
    in;
    send;
    recv;
}
client::client(buffer &_in, ssocket &new_socket) {
    in = &_in;
    socket.Swap(new_socket);
    send = thread(sending, ref(*this));
    recv = thread(recving, ref(*this));
    send.detach();
    recv.detach();
}

client::client(client &other) {
    buffer *swap_buff = in;
    in = other.in;
    other.in = swap_buff;
    socket.Swap(other.socket);
    send = thread(sending, ref(*this));
    recv = thread(recving, ref(*this));
    send.detach();
    recv.detach();
}

void sending(client &me) {
    while (true) {
        if (me.out.Size() > 0) {
            me.socket.send_buff(me.out);
        }
    }
}
void recving(client &me) {
    while (true) {
        me.socket.recv_buff(*me.in);
    }
}


sserver::sserver() {
    listener.Bind();
    listener.Listen();
    listen = thread(accepting_clients, ref(*this));
    listen.detach();
}
int sserver::num_of_clients() {
    return clients.size();
}

void accepting_clients(sserver &serv) {
    while (true) {
        ssocket new_socket;
        new_socket.Accept(serv.listener);
        serv.clients.emplace(serv.clients.size(), client(serv.recved, new_socket));
    }
}
