#include "server.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <iostream>
#include <numeric>
#include <regex>
#include <unistd.h>

const int Server::BUFFER_SIZE = 1024;

/**
 * @brief Привязывается к порту
 * 
 * @param port номер порта
 * @return true если все хорошо
 * @return false если не получилось подключиться
 */
bool Server::connectTo(int port)
{
    if (_listener < 0)
    {
        std::cerr << "Socket is not open" << std::endl;
        return false; 
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(_listener, (sockaddr *)&addr, sizeof(addr)) < 0)
    {
        std::cerr << "Cannot bind to port:" << port << std::endl;
        return false;
    }
    if (!listenToClient())
    {
        std::cerr << "Cannot listen" << std::endl;
        return false; 
    }
    std::cout << "Start listen port " << port << std::endl;
    return true;
}

/**
 * @brief Закрывает сокет
 * 
 * @return true если все закрылось хорошо
 * @return false если все закрылось нехорошо
 */
bool Server::close()
{
    return ::close(_listener) == 0;
}

/**
 * @brief обработка сообщений от клиента
 * 
 * @return true 
 * @return false 
 */
bool Server::run()
{
    while (1)
    {
        if (!acceptClient())
        {
            std::cerr << "Cannot accpet client" << std::endl;
            return false;
        }
        while (1)
        {
            std::string message;
            waitForMessage(message);

            std::cout << message << std::endl;


            if (message == "disconnect")
            {
                sendMessage("Bye");
                sendMessage("Bye");
                break;
            }

            auto res = _processor->process(message);

            std::cout << res.first << " " << res.second << std::endl;
            
            sendMessage(res.first);
            sendMessage(res.second);
        }
    }
}

/**
 * @brief Устанавливает нужный обработчик сообщений
 * 
 * @param processor обработчик 
 */
void Server::setProcessor(std::unique_ptr<StringProcessor> processor)
{
    _processor = std::move(processor);
}
