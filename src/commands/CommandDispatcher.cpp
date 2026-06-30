#include "commands/CommandDispatcher.hpp"

CommandDispatcher::CommandDispatcher() {}

std::string CommandDispatcher::dispatch(const Command &command) {
  // ===========================
  // SET
  // ===========================

  if (command.name == "SET") {
    if (command.arguments.size() != 2) {
      return "ERROR: SET requires key and value";
    }

    storageEngine.set(command.arguments[0], command.arguments[1]);

    return "OK";
  }

  // ===========================
  // GET
  // ===========================

  if (command.name == "GET") {
    if (command.arguments.size() != 1) {
      return "ERROR: GET requires key";
    }

    auto value = storageEngine.get(command.arguments[0]);

    if (value) {
      return *value;
    }

    return "NULL";
  }

  // ===========================
  // DEL
  // ===========================

  if (command.name == "DEL") {
    if (command.arguments.size() != 1) {
      return "ERROR: DEL requires key";
    }

    bool removed = storageEngine.del(command.arguments[0]);

    return removed ? "1" : "0";
  }

  // ===========================
  // EXISTS
  // ===========================

  if (command.name == "EXISTS") {
    if (command.arguments.size() != 1) {
      return "ERROR: EXISTS requires key";
    }

    bool exists = storageEngine.exists(command.arguments[0]);

    return exists ? "1" : "0";
  }

  return "ERROR: Unknown command";
}