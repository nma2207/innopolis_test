#pragma once

#include <memory>

#include "stringprocessor.h"

/**
 * @brief Сервер
 * 
 */
class Server
{
public:
    // enum Type
    // {
    //     UDP,
    //     TCP
    // };

    // Server(Type type);
    bool connectTo(int port);
    bool close();
    bool run();    

    void setProcessor(std::unique_ptr<StringProcessor> processor);

    static const int BUFFER_SIZE;

protected:
    virtual bool listenToClient() = 0;
    virtual bool acceptClient() = 0;
    virtual bool waitForMessage(std::string&) = 0;
    virtual bool sendMessage(const std::string&) = 0;

    int _listener;

private:
    std::unique_ptr<StringProcessor> _processor;
};