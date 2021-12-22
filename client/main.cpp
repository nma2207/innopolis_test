
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstring>

//char* message = "20 bananas, 15 apples 5peaches and 10 oranges\n";
char buf[1024];

int main(int n, char** args)
{


    int sock;
    struct sockaddr_in addr;
    char* message = args[1];
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {

        return 1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080); // или любой другой порт...
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    inet_aton("127.0.0.1", &(addr.sin_addr));
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        return 2;
    }

    std::cout << message << std::endl;
    send(sock, message, strlen(message) + 1, 0);
    recv(sock, buf, 1024, 0);
    
    std::cout << buf << std::endl;
    recv(sock, buf, 1024, 0);
    
    std::cout << buf << std::endl;


    return 0;
}