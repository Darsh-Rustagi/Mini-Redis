#include "../include/server.hpp"

#include <iostream>

void Server::start() {
  std::cout << "Starting application..." << std::endl;

  if (!tcpserver.initialize(6375)) {
    std::cout << "Failed to initialize TCP server." << std::endl;
    return;
  }
  tcpserver.start();
}