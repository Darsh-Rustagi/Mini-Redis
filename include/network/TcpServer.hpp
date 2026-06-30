#pragma once

#include "commands/CommandDispatcher.hpp"
#include "protocol/CommandParser.hpp"

class TcpServer {
public:
  TcpServer();
  ~TcpServer();

  bool initialize(int port);
  void start();

private:
  bool createSocket();
  bool bindSocket(int port);
  bool listenSocket();

  void acceptClients();
  void handleClient(int clientSocket);

  int serverSocket;

  // NEW
  CommandParser commandParser;
  CommandDispatcher commandDispatcher;
};