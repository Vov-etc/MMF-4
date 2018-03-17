#include <iostream>
#include "src/includes/socket_tcp.h"
using namespace std;


int main() {
    ssocket to_ser;
    to_ser.Connect();
    system("pause");
    return 0;
}