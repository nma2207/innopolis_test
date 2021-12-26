#include "client.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <cstdio>
#include <iostream>
#include <unistd.h>

/**
 * @brief Устанавливает параметры сервера
 * 
 * @param serverIp IP-аддрес
 * @param serverPort порт
 * @return true если законнектился
 * @return false не законнектился
 */
bool Client::setServer(const std::string &serverIp, int serverPort)
{
    if (_socket < 0)
    {
        std::cerr << "Socket is not allowed" << std::endl;
        return false;
    }

    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(serverPort);
    inet_aton(serverIp.c_str(), &_serverAddr.sin_addr);

    if (!this->connect())
    {
        std::cerr << "Cannot connect to " << serverIp << ":" << serverPort << std::endl;

        return false;
    }
    return true;
}

/**
 * @brief Закрывает сокет
 */
bool Client::close()
{
    return ::close(_socket) == 0;
}

/**
 * @brief Отправка сообщения на сервер, ждет в ответ 2 сообщения
 * 
 * @param message сообщение
 * @return std::pair<std::string, std::string> результат работы (отсортированный массив и сумма)
 */
std::pair<std::string, std::string> Client::send(const std::string &message)
{
    size_t messageSize = message.size() + 1;
    if (!sendMessage(message))
    {
        std::cerr << "Send message error" << std::endl;
        return {};
    }
    
    std::string response;
    if (!waitForMessage(response, messageSize))
    {
        std::cerr << "Recv error" << std::endl;
        return {};
    }
    
    std::pair<std::string, std::string> result;
    result.first = response;

    if (!waitForMessage(response, messageSize))
    {
        std::cerr << "Recv error" << std::endl;
        return {};
    }
    result.second = response;

    return result;
}