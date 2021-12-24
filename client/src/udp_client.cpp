#include "udp_client.h"

#include <iostream> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

UdpClient::UdpClient()
{
    _socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
}

bool UdpClient::connect()
{
    return true;
}

bool UdpClient::sendMessage(const std::string &message)
{
    std::cout << _serverAddr.sin_addr.s_addr << std::endl;
    return sendto(_socket, message.c_str(), message.size()+1, 0, (sockaddr*)&_serverAddr, sizeof(_serverAddr)) != -1;
}

bool UdpClient::waitForMessage(std::string &message, size_t maxMessageSize)
{
    char* buf = new char[maxMessageSize];
    int len;
    ssize_t code = recvfrom(_socket, buf, maxMessageSize, 0, (struct sockaddr*)&_serverAddr, (socklen_t*)&len);
    
    message = buf;
    return code != -1;
}