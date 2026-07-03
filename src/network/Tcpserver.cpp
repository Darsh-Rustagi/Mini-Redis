#include "../../include/network/TcpServer.hpp"
#include "../../include/protocol/RESPParser.hpp"
#include "../../include/protocol/RESPSerializer.hpp"

#include <array>
#include <cerrno>
#include <cstring>
#include <iostream>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

// =============================
// Constructor / Destructor
// =============================

TcpServer::TcpServer() : serverSocket(-1) {}

TcpServer::~TcpServer() {
  if (serverSocket != -1) {
    close(serverSocket);
  }
}

// =============================
// Public Functions
// =============================

bool TcpServer::initialize(int port) {
  if (!createSocket()) {
    return false;
  }

  if (!bindSocket(port)) {
    return false;
  }

  if (!listenSocket()) {
    return false;
  }

  return true;
}

void TcpServer::start() {
  std::cout << "TCP Server Started." << std::endl;

  acceptClients();
}

// =============================
// Private Functions
// =============================

bool TcpServer::createSocket() {
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  if (serverSocket == -1) {
    std::cerr << "Failed to create socket." << std::endl;
    return false;
  }

  std::cout << "Socket created successfully." << std::endl;

  return true;
}

bool TcpServer::bindSocket(int port) {
  sockaddr_in serverAddress{};

  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(port);
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

  int option = 1;

  if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &option,
                 sizeof(option)) < 0) {
    std::cerr << "setsockopt failed: " << strerror(errno) << std::endl;

    return false;
  }

  if (bind(serverSocket, reinterpret_cast<sockaddr *>(&serverAddress),
           sizeof(serverAddress)) == -1) {
    std::cerr << "Failed to bind socket: " << strerror(errno) << std::endl;

    return false;
  }

  std::cout << "Port bound successfully." << std::endl;

  return true;
}

bool TcpServer::listenSocket() {
  if (listen(serverSocket, SOMAXCONN) == -1) {
    std::cerr << "Failed to listen: " << strerror(errno) << std::endl;

    return false;
  }

  std::cout << "Listening on port 6375..." << std::endl;

  return true;
}

void TcpServer::acceptClients() {
  while (true) {
    std::cout << "Waiting for clients..." << std::endl;

    sockaddr_in clientAddress{};
    socklen_t clientLength = sizeof(clientAddress);

    int clientSocket =
        accept(serverSocket, reinterpret_cast<sockaddr *>(&clientAddress),
               &clientLength);

    if (clientSocket == -1) {
      std::cerr << "accept failed: " << strerror(errno) << std::endl;
      continue;
    }

    std::cout << "Client connected." << std::endl;

    handleClient(clientSocket);
  }
}

void TcpServer::handleClient(int clientSocket) {

    RESPParser respParser;

    while (true) {

        std::array<char, 1024> buffer{};

        ssize_t bytesReceived =
            recv(clientSocket, buffer.data(), buffer.size(), 0);

        if (bytesReceived > 0) {

            std::string request(buffer.data(), bytesReceived);

            //------------------------------------------------
            // Parse RESP
            //------------------------------------------------

            std::vector<std::string> args;

            try {
                args = respParser.parse(request);
            }
            catch (...) {

                std::string error =
                    RESPSerializer::error("ERR Protocol Error");

                send(clientSocket,
                     error.c_str(),
                     error.size(),
                     0);

                continue;
            }

            //------------------------------------------------
            // Convert arguments into command string
            //------------------------------------------------

            std::string message;

            for (const auto &arg : args) {

                if (!message.empty())
                    message += " ";

                message += arg;
            }

            std::cout << "Received: " << message << std::endl;

            //------------------------------------------------
            // Parse command
            //------------------------------------------------

            Command command = commandParser.parse(message);

            //------------------------------------------------
            // Execute command
            //------------------------------------------------

            std::string response = commandDispatcher.dispatch(command);

            //------------------------------------------------
            // Send response (already RESP encoded)
            //------------------------------------------------

            ssize_t bytesSent =
                send(clientSocket,
                    response.c_str(),
                    response.size(),
                    0);

            if (bytesSent == -1) {

                std::cerr << "send failed: "
                          << strerror(errno)
                          << std::endl;

                break;
            }
        }
        else if (bytesReceived == 0) {

            std::cout << "Client disconnected."
                      << std::endl;

            break;
        }
        else {

            std::cerr << "recv failed: "
                      << strerror(errno)
                      << std::endl;

            break;
        }
    }

    close(clientSocket);

    std::cout << "Connection closed."
              << std::endl;
}