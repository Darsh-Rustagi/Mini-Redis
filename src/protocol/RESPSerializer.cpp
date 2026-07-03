#include "protocol/RESPSerializer.hpp"

std::string RESPSerializer::simpleString(const std::string& value)
{
    return "+" + value + "\r\n";
}

std::string RESPSerializer::bulkString(const std::string& value)
{
    return "$" +
           std::to_string(value.size()) +
           "\r\n" +
           value +
           "\r\n";
}

std::string RESPSerializer::nullBulkString()
{
    return "$-1\r\n";
}

std::string RESPSerializer::error(const std::string& value)
{
    return "-" + value + "\r\n";
}

std::string RESPSerializer::integer(long long value)
{
    return ":" + std::to_string(value) + "\r\n";
}