#pragma once

class TcpServer
{
public:
    TcpServer();
    ~TcpServer();
    bool initialize(int port);
    void start();

private:
    int serverSocket;

};  