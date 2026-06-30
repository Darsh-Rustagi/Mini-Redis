#include "../include/server.hpp"

#include <iostream>

void Server::start() {
  std::cout << "Starting application..." << std::endl;

  if (!tcpServer.initialize(6379)) {
    std::cout << "Failed to initialize TCP server." << std::endl;
    return;
  }

  tcpServer.start();
}