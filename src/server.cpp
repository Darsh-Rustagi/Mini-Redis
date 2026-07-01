#include "server.hpp"

#include <iostream>

void Server::start(int port) {
  std::cout << "Starting application..." << std::endl;

  if (!tcpserver.initialize(port)) {
    std::cout << "Failed to initialize TCP server." << std::endl;
    return;
  }
  tcpserver.start();
}