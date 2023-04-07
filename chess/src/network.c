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

int CreateClient(const char* server_port) {
    host.type = HOST_CLIENT;
    host.client.connect_socket = INVALID_SOCKET;
    
    WSADATA wsaData;
    struct addrinfo* result = NULL;
    struct addrinfo* ptr = NULL;
    struct addrinfo hints;

    host.result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (host.result != 0) {
       LOG_ERROR("WSAStartup failed");
        return -1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    host.result = getaddrinfo("127.0.0.1", server_port, &hints, &result);

    if (host.result != 0)
    {
        LOG_ERROR("getaddrinfo failed");
        WSACleanup();
        return -1;
    }

    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        
        host.client.connect_socket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);

        if (host.client.connect_socket == INVALID_SOCKET) {
            LOG_ERROR("socket failed");
            WSACleanup();
            return -1;
        }

        host.result = connect(host.client.connect_socket, ptr->ai_addr, (int)ptr->ai_addrlen);

        if (host.result == SOCKET_ERROR)
        {
            closesocket(host.client.connect_socket);
            host.client.connect_socket = INVALID_SOCKET;
            LOG_ERROR("The server is down... did not connect");
        }
    }

    freeaddrinfo(result);

    if (host.client.connect_socket == INVALID_SOCKET)
    {
        LOG_ERROR("Unable to connect to server!");
        WSACleanup();
        return -1;
    }

    u_long argp = 1;

    host.result = ioctlsocket(host.client.connect_socket, FIONBIO, &argp);
    if (host.result == SOCKET_ERROR)
    {
        //LOG_ERROR(WSAGetLastError());
        closesocket(host.client.connect_socket);
        WSACleanup();
        return -1;
    }

    return host.result;

}

int CreateServer(const char* server_port) {
    host.type = HOST_SERVER;
    host.server.listening_socket = INVALID_SOCKET;
    host.server.client_socket = INVALID_SOCKET;

    WSADATA wsaData;
    struct addrinfo* result = NULL;
    struct addrinfo hints;
    
    host.result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (host.result != 0) {
        LOG_ERROR("WSAStartup failed");
        return -1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    host.result = getaddrinfo(NULL, server_port, &hints, &result);

    if (host.result != 0) {
        LOG_ERROR("getaddrinfo failed");
        WSACleanup();
        return -1;
    }

    host.server.listening_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (host.server.listening_socket == INVALID_SOCKET) {
        LOG_ERROR("socket failed");
        freeaddrinfo(result);
        WSACleanup();
        return -1;
    }

    u_long argp = 1;
    host.result = ioctlsocket(host.server.listening_socket, FIONBIO, &argp);

    if (host.result == SOCKET_ERROR) {
        //LOG_ERROR(WSAGetLastError());
        closesocket(host.server.listening_socket);
        WSACleanup();
        return -1;
    }

    host.result = bind(host.server.listening_socket, result->ai_addr, (int)result->ai_addrlen);

    if (host.result == SOCKET_ERROR) {
        //LOG_ERROR(WSAGetLastError());
        freeaddrinfo(result);
        closesocket(host.server.listening_socket);
        WSACleanup();
        return -1;
    }

    freeaddrinfo(result);

    host.result = listen(host.server.listening_socket, SOMAXCONN);

    if (host.result == SOCKET_ERROR) {
        //LOG_ERROR(WSAGetLastError());
        closesocket(host.server.listening_socket);
        WSACleanup();
        return -1;
    }

    return host.result;

}

void CloseConnection() {

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

bool AcceptClient() {
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


int GetHostType() {
    return host.type;
}