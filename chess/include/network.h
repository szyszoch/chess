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

int get_host_type();

bool create_client(const char* server_addr, const char* server_port);

bool create_server(const char* server_port);
bool accept_client();

void close_connection();
bool send_message(char* msg, int msg_len);
bool receive_message(char* buff, int buff_len);
bool is_connected();