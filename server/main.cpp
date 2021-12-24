#include <iostream>
#include <regex>

#include <server.h>
#include "numbersprocessor.h"


int main(int n, char** args)
{

    if (n != 3)
    {
        std::cout << "we need 4 arguments: TCP/UDP, ip address and port of server" << std::endl;
        return 0;
    }

    Server::Type type = std::string{args[1]} == "TCP" ? Server::TCP : Server::UDP;
    int port = std::stoi(args[2]);
    
    Server server{type};
    if (!server.start(port))
    {
        std::cout << "Server cannot start" << std::endl;
        return 1;
    }

    server.setProcessor(std::make_unique<NumbersProcessor>());
    if (!server.run())
    {
        std::cout << "Server failed" << std::endl;
        return 1;
    }
 //   server.close();
}
