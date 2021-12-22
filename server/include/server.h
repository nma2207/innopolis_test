#pragma once

class Server
{
public:
    enum Type
    {
        UDP,
        TCP
    };

    Server(Type type);
    ~Server();
    bool start(int port);
    bool run();
    static const int BUFFER_SIZE;

private:
    int _listener;
};