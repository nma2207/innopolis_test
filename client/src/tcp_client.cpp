#include "tcp_client.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

TcpClient::TcpClient()
{
    _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

bool TcpClient::connect()
{
    return ::connect(_socket, (sockaddr*)&_serverAddr, (sizeof(_serverAddr))) != -1;
}

bool TcpClient::sendMessage(const std::string &message)
{
    return ::send(_socket, message.c_str(), message.size() + 1, 0) != -1;
}

bool TcpClient::waitForMessage(std::string &message, size_t maxMessageSize)
{
    char* buf = new char[maxMessageSize];
    ssize_t code = recv(_socket, buf, maxMessageSize, 0);
    message = buf;
    return code != -1;
}