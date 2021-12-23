#pragma once

#include <memory>
#include "stringprocessor.h"
class Server
{
public:
    enum Type
    {
        UDP,
        TCP
    };

    Server(Type type);
    ~Server();
    bool start(int port);
    bool run();
    void setProcessor(std::unique_ptr<StringProcessor> processor);
    static const int BUFFER_SIZE;

private:
    int _listener;
    std::unique_ptr<StringProcessor> _processor;
};