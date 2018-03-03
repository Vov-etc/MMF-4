#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include "library.h"
using namespace std;


void init(string library_f = "library", string nature_f = "nature") {
    srand(time(0)); 
    ios::sync_with_stdio(false);

    //library_gen(library_f, 10);
    library_fill(library_f);
    nature_gen(nature_f, 20);
    nature_fill(nature_f);
}


int main() {
    init();
    //sort(nature.begin(), nature.end());
    //nat_draw();
    library;
    nature;
    while (1) {
        nat_print();
        system("sleep 0.1");
    }
    system("pause");
    return 0;
}