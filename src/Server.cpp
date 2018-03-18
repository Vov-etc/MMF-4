#define UNICODE
#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <io.h>
#include <fcntl.h>
#include "includes/library.h"
#include "includes/sserver.h"
using namespace std;


void init(string library_f = "library", string nature_f = "nature") {
    srand(time(0));
    ios::sync_with_stdio(false);

    //library_gen(library_f, 10);
    library_fill(library_f);
    //nature_gen(nature_f, 20);
    nature_fill(nature_f);
}


int main() {
    //init();
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);
    sserver serv;
    while (true) {
        vector<wchar_t> data;
        wstring wstr;
        getline(wcin, wstr);
        for (auto el : wstr) {
            data.push_back(el);
        }
        serv.send_to(0, data);
        if (data.size() > 0 && data[0] == '~') {
            if (data.size() > 1 && data[1] == '~') {
                break;
            }
        }
    }
    system("pause");
    return 0;
}