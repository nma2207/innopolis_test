
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>

char message[] = "20 bananas, 15 apples 5peaches and 10 oranges\n";
char buf[sizeof(message)];

int main()
{
    int sock;
    struct sockaddr_in addr;

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

    send(sock, message, sizeof(message), 0);
    recv(sock, buf, sizeof(message), 0);
    
    std::cout << buf << std::endl;
    recv(sock, buf, sizeof(message), 0);
    
    std::cout << buf << std::endl;


    return 0;
}