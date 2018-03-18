#include <iostream>
#include <vector>
#include <string>
#include <io.h>
#include <fcntl.h>
#include "includes/ssocket.h"
using namespace std;


int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);
    wstring server_in_addr;
    string str;
    wcin >> server_in_addr;
    for (auto el : server_in_addr) {
        str += (char)el;
    }
    ssocket to_ser;
    to_ser.Connect(str);
    if (!to_ser.get_last_error()) {
        wcout << "you have received this messages:" << endl;
        while (true) {
            vector<wchar_t> a;
            to_ser.Recv(a);
            for (auto el : a) {
                wcout << el;
            }
            wcout << endl;
            if (a.size() > 0 && a[0] == '~') {
                break;
            }
        }
    }
    system("pause");
    return 0;
}