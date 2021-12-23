#include <client.h>
#include <iostream>
//char* message = "20 bananas, 15 apples 5peaches and 10 oranges\n";
//char buf[1024];

int main(int n, char** args)
{
    if (n != 4)
    {
        std::cout << "we need 4 arguments: TCP/UDP, ip address and port of server" << std::endl;
        return 0;
    }

    Client::Type type = std::string{args[1]} == "TCP" ? Client::TCP : Client::UDP;
    std::string serverIp = args[2];
    int port = std::stoi(args[3]);

    Client client(type);
    if (!client.connectTo(serverIp, port))
    {
        std::cout << "cannot connect" << std::endl;
        return 0;
    }
    std::cout << "COnnected to " << serverIp << ":" << port <<std::endl;
    std::cout <<"Write your message:" << std::endl;
    std::cout << "> ";
    std::string message;
    std::getline(std::cin, message);

    while (message != "quit")
    {
        auto res = client.send(message);
        std::cout << res.first << std::endl
            << res.second << std::endl;

            std::cout << "> ";
        std::getline(std::cin, message);
    }
    // auto res = client.send("20 apples, 30 bananas, 15 peaches and 1 watermelon");
    // std::cout << res.first << std::endl
    //         << res.second << std::endl;

    // res = client.send("20 bananas, 15 apples 5peaches and 10 oranges\n");
    // std::cout << res.first << std::endl
    //         << res.second << std::endl;
    // // int sock;
    // struct sockaddr_in addr;
    // char* message = args[1];
    // sock = socket(AF_INET, SOCK_STREAM, 0);
    // if(sock < 0)
    // {

    //     return 1;
    // }

    // addr.sin_family = AF_INET;
    // addr.sin_port = htons(8080); // или любой другой порт...
    // addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    // inet_aton("127.0.0.1", &(addr.sin_addr));
    // if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    // {
    //     return 2;
    // }

    // std::cout << message << std::endl;
    // send(sock, message, strlen(message) + 1, 0);
    // recv(sock, buf, 1024, 0);
    
    // std::cout << buf << std::endl;
    // recv(sock, buf, 1024, 0);
    
    // std::cout << buf << std::endl;


    return 0;
}