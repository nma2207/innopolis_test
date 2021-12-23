#include "client.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <cstdio>
#include <iostream>

Client::Client(Type type)
{
    switch (type)
    {
    case UDP:
        _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_UDP);
        break;
    case TCP:
        _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        break;
    }
}

bool Client::connectTo(const std::string& serverIp, int serverPort)
{
    if (_socket < 0)
    {
        std::cerr << "Socket is not allowed" << std::endl;
        return false;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(serverPort);
    inet_aton(serverIp.c_str(), &addr.sin_addr);

    if (connect(_socket, (sockaddr*)&addr, sizeof(addr)) < 0)
    {
        std::cerr << "Cannot connect to " << serverIp <<":"<<serverPort << std::endl;

        return false;
    }
    return true;
}

bool Client::close()
{
    return true;
}

std::pair<std::string, std::string> Client::send(const std::string& message)
{
    size_t messageSize = message.size() + 1;
    ::send(_socket, message.c_str(), messageSize, 0);
    char *buf = new char[messageSize];
    recv(_socket, buf, messageSize, 0);
    std::pair<std::string, std::string> result;
    result.first = buf;

    recv(_socket, buf, messageSize, 0);
    result.second = buf;

    delete[] buf;

    return result;
}