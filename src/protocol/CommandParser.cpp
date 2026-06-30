#include "protocol/CommandParser.hpp"

#include <sstream>

Command CommandParser::parse(const std::string &input) {
  Command command;

  std::istringstream stream(input);

  // First token is the command name
  stream >> command.name;

  // Remaining tokens are arguments
  std::string argument;

  while (stream >> argument) {
    command.arguments.push_back(argument);
  }

  return command;
}