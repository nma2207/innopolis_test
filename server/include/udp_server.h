#pragma once

#include "server.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/**
 * @brief UDP-сервер
 * 
 */
class UdpServer : public Server
{
public:
    UdpServer();

protected:
    bool listenToClient() override;
    bool acceptClient() override;
    bool waitForMessage(std::string &) override;
    bool sendMessage(const std::string &) override;
    

private:
    sockaddr_in _clientAddres;
    socklen_t _clientLen;
};