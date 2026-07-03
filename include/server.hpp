#pragma once

#include "network/TcpServer.hpp"

class Server {
public:
  bool start(int port);

private:
  TcpServer tcpserver;
};