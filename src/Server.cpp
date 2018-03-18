#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include "includes/library.h"
#include "includes/ssocket.h"
#include <thread>
using namespace std;


void init(string library_f = "library", string nature_f = "nature") {
    srand(time(0));
    ios::sync_with_stdio(false);

    //library_gen(library_f, 10);
    library_fill(library_f);
    //nature_gen(nature_f, 20);
    nature_fill(nature_f);
}

void tFunc(int a, int num) {
    for (int i = 1; i < 10; i++) {
        a += i;
    }
    cout << a << endl;
}


int main() {
    init();
    int a = 0;
    thread t2(tFunc, a + 10, 0), t1(tFunc, a, 1);
    cout << "AsDF" << endl;
    t1.join();
    t2.join();
    /*ssocket listener, to_cli;
    listener.Bind();
    listener.Listen();
    to_cli.Accept(listener);*/
    system("pause");
    return 0;
}