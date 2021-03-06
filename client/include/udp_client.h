#pragma once

#include "client.h"

/**
 * @brief UDP-клиент
 * 
 */
class UdpClient : public Client
{
public:
    UdpClient();

protected:
    virtual bool connect();
    bool sendMessage(const std::string &message);
    bool waitForMessage(std::string &message, size_t maxMessageSize);
};