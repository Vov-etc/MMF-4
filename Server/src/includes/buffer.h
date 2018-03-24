#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class buffer {
    char *data;
    int size;
    bool is_locked;
public:
    buffer(int _size = 0);

    int Size() const;
    char* Data() const;

    void resize(int len);
    void lock();
    void unlock();

    void getline();
    void stobuff(string str);
    void wstobuff(wstring wstr);
    template <typename T>
    void vtobuff(vector<T> vec) {
        lock();
        size = vec.size() * sizeof(T) / sizeof(char);
        resize(size);
        memcpy_s(data, size, vec.data(), size);
        unlock();
    }
};

#endif // !BUFFER_H
