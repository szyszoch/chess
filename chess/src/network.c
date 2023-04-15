#include "network.h"

typedef struct Client {
    SOCKET connect_socket;
} Client;

typedef struct Server {
    SOCKET listening_socket;
    SOCKET client_socket;
} Server;

typedef struct Host {
    int type;
    union HostType {
        Client client;
        Server server;
    };
    int result;
} Host;

Host host;

bool create_client(const char* server_port) 
{
    host.type = HOST_CLIENT;
    host.client.connect_socket = INVALID_SOCKET;
    
    WSADATA wsaData;
    struct addrinfo* result = NULL;
    struct addrinfo* ptr = NULL;
    struct addrinfo hints;

    host.result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (host.result != 0) {
        LOG_ERROR(SDL_LOG_CATEGORY_SYSTEM,"WSAStartup failed");
        goto error_wsa;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    host.result = getaddrinfo("127.0.0.1", server_port, &hints, &result);
    if (host.result != 0) {
        LOG_ERROR(SDL_LOG_CATEGORY_SYSTEM, "getaddrinfo failed");
        goto error_addrinfo;
    }

    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {     
        host.client.connect_socket = socket(ptr->ai_family, ptr->ai_socktype,ptr->ai_protocol);
        if (host.client.connect_socket == INVALID_SOCKET) {
            LOG_ERROR(SDL_LOG_CATEGORY_SYSTEM, "socket failed");
            goto error_connect_socket;
        }

        host.result = connect(host.client.connect_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (host.result == SOCKET_ERROR) {
            closesocket(host.client.connect_socket);
            host.client.connect_socket = INVALID_SOCKET;
            LOG_ERROR(SDL_LOG_CATEGORY_SYSTEM, "The server is down");
        }
    }

    freeaddrinfo(result);

    if (host.client.connect_socket == INVALID_SOCKET) {
        LOG_ERROR(SDL_LOG_CATEGORY_SYSTEM, "Unable to connect to server");
        goto error_connect;
    }

    u_long argp = 1;
    host.result = ioctlsocket(host.client.connect_socket, FIONBIO, &argp);
    if (host.result == SOCKET_ERROR) {
        goto error_socket;
    }

    return true;

error_socket:
    closesocket(host.client.connect_socket);
error_connect:
error_connect_socket:
error_addrinfo:
    WSACleanup();
error_wsa:
    return false;
}

bool create_server(const char* server_port) 
{
    host.type = HOST_SERVER;
    host.server.listening_socket = INVALID_SOCKET;
    host.server.client_socket = INVALID_SOCKET;

    WSADATA wsaData;
    struct addrinfo* result = NULL;
    struct addrinfo hints;
    
    host.result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (host.result != 0) {
        LOG_ERROR(SDL_LOG_CATEGORY_SYSTEM, "WSAStartup failed");
        goto error_wsa;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    host.result = getaddrinfo(NULL, server_port, &hints, &result);
    if (host.result != 0) {
        LOG_ERROR(SDL_LOG_CATEGORY_SYSTEM, "getaddrinfo failed");
        goto error_addrinfo;
    }

    host.server.listening_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (host.server.listening_socket == INVALID_SOCKET) {
        LOG_ERROR(SDL_LOG_CATEGORY_SYSTEM, "socket failed");
        goto error_listening_socket;
    }

    u_long argp = 1;
    host.result = ioctlsocket(host.server.listening_socket, FIONBIO, &argp);
    if (host.result == SOCKET_ERROR) {
        goto error_socket;
    }

    host.result = bind(host.server.listening_socket, result->ai_addr, (int)result->ai_addrlen);
    if (host.result == SOCKET_ERROR) {
        goto error_socket;
    }

    host.result = listen(host.server.listening_socket, SOMAXCONN);
    if (host.result == SOCKET_ERROR) {
        goto error_socket;
    }

    freeaddrinfo(result);

    return true;

error_socket:
    closesocket(host.server.listening_socket);
error_listening_socket:
    freeaddrinfo(result);
error_addrinfo:
    WSACleanup();
error_wsa:
    return false;
}

void close_connection() 
{
    if (host.type == HOST_CLIENT) {
        closesocket(host.client.connect_socket);
    }
    else {
        closesocket(host.server.listening_socket);
        closesocket(host.server.client_socket);
    }

    WSACleanup();

    host.type = 0;
    host.result = 0;
}

bool accept_client() 
{
    host.server.client_socket = accept(host.server.listening_socket, NULL, NULL);
    return host.server.client_socket != INVALID_SOCKET;
}

bool send_message(char* msg, int msg_len)
{
    int result;

    if (host.type == HOST_CLIENT)
        result = send(host.client.connect_socket, msg, msg_len, 0);  
    else 
        result = send(host.server.client_socket, msg, msg_len, 0);

    return (result != SOCKET_ERROR);
}

bool receive_message(char* buff, int buff_len)
{
    int result;

    if (host.type == HOST_CLIENT)
        result = recv(host.client.connect_socket, buff, buff_len, 0);
    else
        result = recv(host.server.client_socket, buff, buff_len, 0);
    
    return (result > 0);
}

int get_host_type() 
{
    return host.type;
}

bool is_connected()
{
    if (host.type == HOST_CLIENT) {
        return !(host.client.connect_socket == INVALID_SOCKET);
    }
    else {
        return !(host.server.client_socket == INVALID_SOCKET);
    }
}