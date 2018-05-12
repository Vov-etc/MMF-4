#include <iostream>
#include <vector>
#include <string>
#include "includes/ssocket.h"
using namespace std;


int main() {
    string server_in_addr;
    string str;
    //wcin >> server_in_addr;
    for (auto el : server_in_addr) {
        str += (char)el;
    }
    ssocket to_ser;
    to_ser.Connect();
    if (to_ser.Is_Open()) {
        cout << "you have received this messages:" << endl;
        while (true) {
            buffer buff;
            to_ser.recv_buff(buff);
            if (buff.Size() >= 0) {
                buff.print();
            } else {
                break;
            }
        }
    } else {
       cerr << WSAGetLastError() << endl;
    }
    system("pause");
    return 0;
}