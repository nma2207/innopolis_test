#include "udp_server.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "unistd.h"

#include <iostream>

UdpServer::UdpServer()
{
    std::cout << "Udp server is created" << std::endl;
    _listener = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    _clientLen = sizeof(_clientAddres);
}

/**
 * Для UDP-сервера не нужен метод listen, но для TCP нужен
 */
bool UdpServer::listenToClient()
{
    return true;
}

/**
 * не нужен для udp, но нужен для tcp
 */
bool UdpServer::acceptClient()
{
    return true;
}

bool UdpServer::waitForMessage(std::string &message)
{
    char buf[Server::BUFFER_SIZE];
    ssize_t bytesRead = recvfrom(_listener, buf, Server::BUFFER_SIZE, 0, (sockaddr*)&this->_clientAddres, &this->_clientLen);
    message = buf;
    return bytesRead != -1;
}

bool UdpServer::sendMessage(const std::string &message)
{  
    return sendto(_listener, message.c_str(), message.size() + 1, 0, (struct sockaddr*)&_clientAddres, _clientLen) != -1;
}
