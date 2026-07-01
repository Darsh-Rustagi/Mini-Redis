#include "config/config.hpp"
#include "server.hpp"

#include <iostream>

int main(int argc, char *argv[]) {
  Config config;

  if (argc > 1) {
    try {
      config.setPort(std::stoi(argv[1]));
    } catch (...) {
      std::cerr << "Invalid port number.\n";
      return 1;
    }
  }

  Server server;

  server.start(config.getPort());

  return 0;
}