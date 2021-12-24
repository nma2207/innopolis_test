#include "udp_server.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <iostream>
UdpServer::UdpServer()
{
    std::cout << "Udp server is created" << std::endl;
    _listener = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
}

bool UdpServer::listenToClient()
{
    return true;
}

bool UdpServer::acceptClient()
{
    return true;
}

bool UdpServer::waitForMessage(std::string &message)
{
    char buf[Server::BUFFER_SIZE];
    recvfrom(_listener, buf, Server::BUFFER_SIZE, 0, &_clientAddres, &_clientLen);
    //int bytes_read = recv(_clientSock, buf, Server::BUFFER_SIZE, 0);
    message = buf;
    return true;
}

bool UdpServer::sendMessage(const std::string &message)
{
    return sendto(_listener, message.c_str(), message.size() + 1, 0, (struct sockaddr*)&_clientAddres, _clientLen) != -1;
}
