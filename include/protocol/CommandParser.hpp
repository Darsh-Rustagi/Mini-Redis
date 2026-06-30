#pragma once

#include "protocol/Command.hpp"

#include <string>

class CommandParser {
public:
  CommandParser() = default;

  // Parse raw client input into a Command object
  Command parse(const std::string &input);
};