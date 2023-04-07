#pragma once
#include <stdbool.h>
#include "log.h"

#define DEFAULT_BUFLEN 512

#define HOST_CLIENT 0
#define HOST_SERVER 1

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

int GetHostType();

int CreateClient(const char* server_port);

int CreateServer(const char* server_port);
bool AcceptClient();

void CloseConnection();
bool send_message(char* msg, int msg_len);
bool receive_message(char* buff, int buff_len);
