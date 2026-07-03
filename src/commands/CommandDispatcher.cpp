#include "commands/CommandDispatcher.hpp"
#include "protocol/RESPSerializer.hpp"

CommandDispatcher::CommandDispatcher() {}

// ===========================
// Dispatch Command
// ===========================

std::string CommandDispatcher::dispatch(const Command &command) {


    // ===========================
    // PING
    // ===========================

    if (command.name == "PING") {
        if (command.arguments.empty()) {
            return RESPSerializer::simpleString("PONG");
        }

        if (command.arguments.size() == 1) {
            return RESPSerializer::bulkString(command.arguments[0]);
        }

        return RESPSerializer::error(
            "ERR wrong number of arguments for 'PING'");
    }

    // ===========================
    // SET
    // ===========================

    if (command.name == "SET") {
        if (command.arguments.size() != 2) {
            return RESPSerializer::error(
                "ERR wrong number of arguments for 'SET'");
        }

        storageEngine.set(command.arguments[0], command.arguments[1]);

        return RESPSerializer::simpleString("OK");
    }

    // ===========================
    // GET
    // ===========================

    if (command.name == "GET") {
        if (command.arguments.size() != 1) {
            return RESPSerializer::error(
                "ERR wrong number of arguments for 'GET'");
        }

        auto value = storageEngine.get(command.arguments[0]);

        if (value.has_value()) {
            return RESPSerializer::bulkString(value.value());
        }

        return RESPSerializer::nullBulkString();
    }

    // ===========================
    // DEL
    // ===========================

    if (command.name == "DEL") {
        if (command.arguments.size() != 1) {
            return RESPSerializer::error(
                "ERR wrong number of arguments for 'DEL'");
        }

        bool removed = storageEngine.del(command.arguments[0]);

        return RESPSerializer::integer(removed ? 1 : 0);
    }

    // ===========================
    // EXISTS
    // ===========================

    if (command.name == "EXISTS") {
        if (command.arguments.size() != 1) {
            return RESPSerializer::error(
                "ERR wrong number of arguments for 'EXISTS'");
        }

        bool exists = storageEngine.exists(command.arguments[0]);

        return RESPSerializer::integer(exists ? 1 : 0);
    }

    // ===========================
    // Unknown Command
    // ===========================

    return RESPSerializer::error("ERR unknown command");
}