#pragma once
#include <stdbool.h>
#include "log.h"

#define DEFAULT_BUFLEN 512

#ifdef _WIN32

#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#else
  
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h> 
#include <unistd.h>

#endif

int CreateClient(const char* server_port);

int CreateServer(const char* server_port);
bool AcceptClient();

void CloseConnection();
int SendMsg(char* message, int messageSize);
int ReceiveMsg(char* buffer, int bufSize);
