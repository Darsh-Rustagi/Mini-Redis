#pragma once

#include "network/TcpServer.hpp"

class Server {
public:
  void start();

private:
  TcpServer tcpServer;
};