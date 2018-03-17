#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include "includes/library.h"
#include "includes/socket_tcp.h"
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
    init();
    ssocket listener, to_cli;
    listener.Bind();
    listener.Listen();
    to_cli.Accept(listener);
    system("pause");
    return 0;
}