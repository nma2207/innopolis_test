#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>
#include <utility>

class Client
{
public:
    bool setServer(const std::string &serverIp, int serverPort);
    bool close();
    std::pair<std::string, std::string> send(const std::string &message);

protected:
    virtual bool connect() = 0;
    virtual bool sendMessage(const std::string &message) = 0;
    virtual bool waitForMessage(std::string &message, size_t maxMessageSize) = 0;

    int _socket;
    sockaddr_in _serverAddr;
};