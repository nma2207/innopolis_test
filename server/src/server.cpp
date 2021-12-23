#include "server.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <iostream>
#include <regex>
#include <numeric>

const int Server::BUFFER_SIZE = 1024;

Server::Server(Server::Type type)
{
    switch (type)
    {
    case TCP:
        _listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        break;
    case UDP:
        _listener = socket(AF_INET, SOCK_STREAM, IPPROTO_UDP);
        break;
    }
}

bool Server::start(int port)
{
    if (_listener < 0)
    {
        return false;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(_listener, (sockaddr *)&addr, sizeof(addr)) < 0)
    {
        std::cerr << "err";
        return false;
    }

    listen(_listener, 5);
    std::cout << "Start listen port " << port << std::endl;
    return true;
}

bool Server::run()
{
    while (1)
    {
        int sock = accept(_listener, nullptr, nullptr);
        if (sock < 0)
        {
            return false;
        }
        while (1)
        {
            char buf[Server::BUFFER_SIZE];
            int bytes_read = recv(sock, buf, 1024, 0);
            if (bytes_read <= 0)
                break;

            std::cout << buf << std::endl;

            auto res = _processor->process(buf);
            
            std::cout << res.first << " " << res.second << std::endl;
            send(sock, res.first.c_str(), res.first.size() + 1, 0);
            send(sock, res.second.c_str(), res.second.size() + 1, 0);
        }
    }
}

void Server::setProcessor(std::unique_ptr<StringProcessor> processor)
{
    _processor = std::move(processor);
}
Server::~Server()
{
}