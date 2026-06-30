#pragma once

#include <string>
#include <vector>

struct Command {
  // Command name
  // Examples:
  // SET
  // GET
  // DEL
  // EXISTS
  std::string name;

  // Command arguments
  // Example:
  //
  // SET name Alice
  //
  // arguments[0] = "name"
  // arguments[1] = "Alice"
  std::vector<std::string> arguments;
};