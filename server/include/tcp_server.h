#pragma once

#include "server.h"

class TcpServer : public Server
{
public:
    TcpServer();

protected:
    bool listenToClient() override;
    bool acceptClient() override;
    bool waitForMessage(std::string &) override;
    bool sendMessage(const std::string &) override;
    

private:
    int _clientSock;
};