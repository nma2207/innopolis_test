#pragma once

#include "client.h"

/**
 * @brief TCP-клиент
 * 
 */
class TcpClient : public Client
{
public:
    TcpClient();

protected:
    virtual bool connect();
    bool sendMessage(const std::string &message);
    bool waitForMessage(std::string &message, size_t maxMessageSize);
};