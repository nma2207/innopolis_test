#include "tcp_server.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <iostream>
TcpServer::TcpServer()
{
    std::cout << "TCP server created" << std::endl;
    _listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

bool TcpServer::listenToClient()
{
    return listen(_listener, 1) != -1;
}

bool TcpServer::acceptClient()
{
    _clientSock = accept(_listener, nullptr, nullptr);
    return _clientSock != -1;
}

bool TcpServer::waitForMessage(std::string &message)
{
    char buf[Server::BUFFER_SIZE];
    int bytes_read = recv(_clientSock, buf, Server::BUFFER_SIZE, 0);
    message = buf;
    return bytes_read != -1;
}

bool TcpServer::sendMessage(const std::string &message)
{
    return send(_clientSock, message.c_str(), message.size() + 1, 0) != -1;
}
