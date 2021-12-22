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

            std::string bufStr = buf;
            std::cout << bufStr << std::endl;

            std::regex rgx("[^\\d]+");
            
            std::sregex_token_iterator iter(bufStr.begin(),
                                            bufStr.end(),
                                            rgx,
                                            -1);
            std::sregex_token_iterator end;

            std::vector<int> numbers;
            for (; iter != end; ++iter)
                numbers.push_back(std::stoi(*iter));
            
            std::sort(numbers.begin(), numbers.end());
            std::stringstream ss;
            for(int num: numbers)
                ss << std::to_string(num) + " ";
            std::string sum = std::to_string(std::accumulate(numbers.begin(), numbers.end(), 0));

            std::cout <<ss.str() << " " << sum << std::endl;
            send(sock, ss.str().c_str(), ss.str().size() + 1, 0);
            send(sock, sum.c_str(), sum.size() + 1, 0);

        }
    }
}

Server::~Server()
{
}