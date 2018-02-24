#include "library.h"
#include <iostream>
#include <fstream>
using namespace std;

int species::amount = 0;
int object::amount = 0;

vector <species> library;
vector <object> nature;

void library_gen(string library_f, int size) {
    fstream fout;
    fout.open(library_f, fstream::out);
    fout << size << endl << endl;
    for (int i = 0; i < size; i++) {
        int len = 12 - rand() % 10;
        for (int j = 0; j < len; j++) {
            char c = 'a' + rand() % 26;
            fout << c;
        }
        fout << endl;
        for (int j = 0; j < 64; j++) {
            char c = 'a' + rand() % 26;
            fout << c;
        }
        fout << endl;
        fout << endl;
    }
    fout.close();
}

void nature_gen(string nature_f, int size) {
    fstream fout;
    fout.open(nature_f, fstream::out);
    fout << size << endl << endl;
    for (int i = 0; i < size; i++) {
        double x = (double)(rand() % (W_X * 1000)) / 1000,
            y = (double)(rand() % (W_Y * 1000)) / 1000;
        int spcy = rand() % LIB_SIZE;
        fout << x << " " << y << " " << spcy << endl;
    }
    fout.close();
}

void library_fill(string library_f) {
    fstream fin;
    fin.open(library_f, fstream::in);
    int n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        string name, dscr;
        fin >> name >> dscr;
        library.emplace_back(name, dscr);
    }
}

void nature_fill(string nature_f) {
    fstream fin;
    fin.open(nature_f, fstream::in);
    int n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        double x, y;
        int spcy;
        fin >> x >> y >> spcy;
        nature.emplace_back(x, y, library[spcy]);
    }
}