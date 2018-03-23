#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class buffer {
    char *data;
    int size;
public:
    buffer():
    data(NULL),
    size(0)
    {};
    void getline();
};

#endif // !BUFFER_H
