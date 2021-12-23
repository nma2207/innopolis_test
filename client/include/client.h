#pragma once

#include <string>
#include <utility>

class Client
{
public:
    enum Type
    {
        UDP,
        TCP
    };
    Client(Type);
    bool connectTo(const std::string& serverIp, int serverPort);
    bool close();
    std::pair<std::string, std::string> send(const std::string& message);

private:
    int _socket;
};