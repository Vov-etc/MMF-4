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

    void lock();
    void unlock();
    bool is_lock();
    void resize(int len);

    void s_cpy_to_buff(string &str);
    void ws_cpy_to_buff(wstring &wstr);
    template <typename T>
    void v_cpy_to_buff(vector<T> vec) {
        lock();
        size = vec.size() * sizeof(T) / sizeof(char);
        resize(size);
        memcpy_s(data, size, vec.data(), size);
        unlock();
    }
    void print();
};

#endif // !BUFFER_H
