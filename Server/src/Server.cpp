#include "includes/sserver.h"
#include "includes/buffer.h"
#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <io.h>
#include <fcntl.h>
//#include "includes/library.h"
using namespace std;


void init(string library_f = "library", string nature_f = "nature") {
    srand(time(0));
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);
    //library_gen(library_f, 10);
    //library_fill(library_f);
    //nature_gen(nature_f, 20);
    //nature_fill(nature_f);
}


int main() {
    init();
    sserver serv;
    while (true) {
        if (serv.clients.size() > 0) {
            int cli = 0;
            wstring wstr;
            vector<wchar_t> data;
            for (auto el : serv.clients) {
                wcout << el.first << " ";
            }
            wcout << endl;
            wcin >> cli;
            wcin.ignore();
            getline(wcin, wstr);
            for (auto &el : wstr) {
                data.push_back(el);
            }
            serv.send_to(cli, data);
            if (data.size() > 0 && data[0] == '~') {
                if (data.size() > 1 && data[1] == '~') {
                    break;
                }
            }
        }
    }
    system("pause");
    return 0;
}