#pragma once

#include "network/TcpServer.hpp"

class Server {
public:
  void start(int port);

private:
  TcpServer tcpserver;
};