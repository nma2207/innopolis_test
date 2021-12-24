#include "client.h"
#include "udp_client.h"
#include "tcp_client.h"

#include <iostream>

#include <memory>
//char* message = "20 bananas, 15 apples 5peaches and 10 oranges\n";
//char buf[1024];

/**
 * @brief метод-фабрика для создания клиента с нужным типом
 * 
 * @param type Тип
 * @return std::unique_ptr<Client> 
 */
std::unique_ptr<Client> clientFactory(const std::string& type)
{
    if (type == "TCP")
        return std::make_unique<TcpClient>();
    else
        return std::make_unique<UdpClient>();
}

int main(int n, char** args)
{
    if (n != 4)
    {
        std::cout << "we need 3 arguments: TCP/UDP, ip address and port of server" << std::endl;
        return 0;
    }

    std::unique_ptr<Client> client = clientFactory(args[1]);
    std::string serverIp = args[2];
    int port = std::stoi(args[3]);

    if (!client->setServer(serverIp, port))
    {
        std::cout << "cannot connect" << std::endl;
        return 0;
    }
    std::cout << "Connected to " << serverIp << ":" << port <<std::endl;
    std::cout <<"Write your message:" << std::endl;

    while (1)
    {
        std::cout << "> ";
        std::string message;
        std::getline(std::cin, message);

        // если пишем quit, то выходим и отсоединяемся от сервера
        if (message == "quit")
        {
            client->send("disconnect");
            break;
        }

        auto res = client->send(message);
        std::cout << res.first << std::endl
            << res.second << std::endl;
    }

    if (!client->close())
    {
        std::cout << "Failed on closing" << std::endl;
    }

    return 0;
}