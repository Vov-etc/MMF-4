#include "includes/buffer.h"


buffer::buffer(int _size) {
    data = new char(_size);
    size = _size;
    is_locked = false;
}

int buffer::Size() const {
    return size;
}
char* buffer::Data() const {
    return data;
}

void buffer::resize(int len) {
    size = len;
    delete data;
    data = new char[len];
}
void buffer::lock() {
    while (is_locked);
    is_locked = true;
}
void buffer::unlock() {
    is_locked = false;
}
bool buffer::is_lock() {
    return is_locked;
}

void buffer::s_cpy_to_buff(string &str) {
    lock();
    size = str.size();
    resize(size);
    memcpy_s(data, size, str.c_str(), size);
    unlock();
}
void buffer::ws_cpy_to_buff(wstring &wstr) {
    lock();
    size = wstr.size() * sizeof(wchar_t) / sizeof(char);
    resize(size);
    memcpy_s(data, size, wstr.c_str(), size);
    unlock();
}

void buffer::print() {
    lock();
    for (int i = 0; i < size; i++) {
        wcout << data[i];
    }
    wcout << endl;
    unlock();
}
