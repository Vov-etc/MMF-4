#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
using namespace std;

static int W_X = 100;
static int W_Y = 1000;
static int LIB_SIZE = 1000;
static int NAT_SIZE = 10000;


class species {
    static int amount;
public:
    string name, dscr;
    species *drop;

    species(string _name = "", string _dscr = "") :
        name(_name),
        dscr(_dscr) {
        amount++;
    }
    ~species() {
        amount--;
    }

};


class block {
    double bias;
    double desity;
    int pattern; //TODO
public:

};


class object {
    static int amount;
    double x, y;
    species type;
    double state;
    int num;
    block *form;
public:
    object(double _x, double _y, species _type, double _state = 1) :
        x(_x),
        y(_y),
        type(_type),
        num(amount),
        state(_state) {
        amount++;
    };
    ~object() {
        amount--;
    }
    double get_x() {
        return x;
    }
    double get_y() {
        return y;
    }
    const species& get_type() const {
        return type;
    }
    int get_num() {
        return num;
    }
    bool operator<(const object &other) const {
        return type.name < other.type.name;
    }
};


extern vector <species> library;
extern vector <object> nature;
void library_gen(string library_f = "library", int n = LIB_SIZE);
void nature_gen(string nature_f = "nature", int n = NAT_SIZE);
void library_fill(string library_f = "library");
void nature_fill(string nature_f = "nature");

#endif // !LIBRARY_H