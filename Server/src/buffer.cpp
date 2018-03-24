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
    lock();
    delete data;
    data = new char(len);
    unlock();
}
void buffer::lock() {
    while (is_locked);
    is_locked = true;
}
void buffer::unlock() {
    is_locked = false;
}

void buffer::getline() {

}
void buffer::stobuff(string str) {
    lock();
    size = str.size();
    resize(size);
    memcpy_s(data, size, str.c_str(), size);
    unlock();
}
void buffer::wstobuff(wstring wstr) {
    lock();
    size = wstr.size() * sizeof(wchar_t) / sizeof(char);
    resize(size);
    memcpy_s(data, size, wstr.c_str(), size);
    unlock();
}