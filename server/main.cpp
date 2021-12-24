#include <iostream>

#include "numbersprocessor.h"

#include "tcp_server.h"
#include "udp_server.h"


std::unique_ptr<Server> serverFactory(const std::string& type)
{
    if (type == "TCP")
        return std::make_unique<TcpServer>();
    else
        return std::make_unique<UdpServer>();
}
int main(int n, char **args)
{
    if (n != 3)
    {
        std::cout << "we need 2 arguments: TCP/UDP and port of server" << std::endl;
        return 0;
    }

    std::unique_ptr<Server> server = serverFactory(args[1]);
    int port = std::stoi(args[2]);

    if (!server->connectTo(port))
    {
        std::cout << "Server cannot connect to port" << port << std::endl;
        return 1;
    }

    server->setProcessor(std::make_unique<NumbersProcessor>());
    if (!server->run())
    {
        std::cout << "Server failed by running" << std::endl;
        return 1;
    }
    if (!server->close())
    {
        std::cout << "Server failed on closing" << std::endl;
        return 1;
    }
}
