#include "library.h"
#include <algorithm>
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
        double x = rand() % (W_X * PREC), y = rand() % (W_Y * PREC);
        x /= PREC;
        y /= PREC;
        int spcy = rand() % library.size();
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

vector<object> nat_search(double x1, double x2, double y1, double y2, string name, double state) {
    vector<object> find;
    for (auto el : nature) {
        if(el.get_x() >= x1 && el.get_x() < x2 &&el.get_y() >= y1 &&el.get_y() < y2 &&
            (name == "" || el.get_type_name() == name) && (state == -1 || el.get_state() == state)) {
            find.emplace_back(el);
        }
    }
    return find;
}

void nat_draw() {
    //system("cls");
    for (int i = 0; i < W_X; i++) {
        for (int j = 0; j < W_Y; j++) {
            vector<object> fst(nat_search(i, i + 1, j, j + 1));
            cout.width(2);
            if (fst.size() > 0) {
                cout << fst[0].get_type_name()[0];
            } else {
                cout << " ";
            }
        }
        cout << " |" << endl;
    }
    for (int j = 0; j < W_Y; j++) {
        cout << "__";
    }
    cout << "_|" << endl;
}

void nat_print() {
    system("cls");
    string out;
    for (int i = 0; i < W_X; i++) {
        for (int j = 0; j < W_Y; j++) {
            out += "  ";
        }
        out += " |\n";
    }
    for (int j = 0; j < W_Y; j++) {
        out += "__";
    }
    out += "_|";
    for (auto el : nature) {
        string name = el.get_type_name();
        int x_pos = ((int)el.get_x()) * ((W_Y + 1) * 2 + 1);
        int y_pos = ((int)el.get_y()) * 2;
        int len = min((int)name.size(), ((W_Y + 1) * 2 - 1 - y_pos));
        out.replace(x_pos + y_pos, len, name, 0, len);
    }
    cout << out << endl;
}