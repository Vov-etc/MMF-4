#include "includes/lobby.h"


player::player() {
    num = time(0) % 10000;
}

void player::Accept(ssocket &listener) {
    my_sock.Accept(listener);
}
void player::Send() {
    thread send(sending, ref(*this));
    send.detach();
}
void player::Recv() {
    thread recv(recving, ref(*this));
    recv.detach();
}

int player::get_num() {
    return num;
}

void sending(player &player) {
    if (player.my_sock.get_socket() != INVALID_SOCKET) {
        if (player.out.Size() > 0) {
            int len = player.out.Size();
            player.my_sock.Send((char*)&len, sizeof(int) / sizeof(char));
            player.out.lock();
            player.my_sock.Send(player.out.Data(), player.out.Size());
            player.out.unlock();
        }
    }
}
void recving(player &player) {
    if (player.my_sock.get_socket() != INVALID_SOCKET) {
        int len = 1000;
        player.my_sock.Recv((char*)&len, sizeof(int) / sizeof(char));
        player.in.lock();
        player.in.resize(len);
        player.my_sock.Recv(player.in.Data(), player.in.Size());
        player.in.unlock();
    }
}




void accepting_clients(lobby &lobby) {
    while (true) {
        int num = lobby.new_player();
        lobby.players[num].Accept(lobby.listener);
    }
}
int lobby::new_player() {
    player new_player;
    players.emplace(pair<int, player>(new_player.get_num(), new_player));
    return new_player.get_num();
}

lobby::lobby() {
    listener.Bind();
    listener.Listen();
    listen = thread(accepting_clients, ref(*this));
    listen.detach();
}
lobby::~lobby() {
}

const map<int, player>& lobby::get_players() const {
    return players;
}
int lobby::num_of_players() {
    return players.size();
}

void lobby::send_to(int num, string &str) {
    players[num].out.s_cpy_to_buff(str);
    players[num].Send();
}
void lobby::recv_from(int num) {
    players[num].Recv();
}
