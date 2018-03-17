#ifndef NET_INCLUDES_H
#define NET_INCLUDES_H

#ifdef _WIN32
#pragma comment ( lib, "ws2_32.lib" )

#include <winsock2.h>

#define errno WSAGetLastError()
#define SERVERADDR "127.0.0.1"
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

typedef int SOCKET;
#endif

const static short PORT = 5050;

#endif // NET_INCLUDES_H
