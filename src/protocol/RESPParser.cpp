#include "protocol/RESPParser.hpp"

#include <stdexcept>

using namespace std;


vector<string> RESPParser::parse(const string& input)
{
    vector<string> result;

    if(input.empty()){
        return result;
    }

    if(input[0] != '*'){
        throw runtime_error("Invalid RESP array");
    }

    size_t pos = 1;
    size_t end = input.find("\r\n", pos);

    int argc = stoi(input.substr(pos, end - pos));

    pos = end + 2;

    for(int i = 0; i < argc; i++){
        if (input[pos] != '$')
            throw std::runtime_error("Expected bulk string");

        pos++;

        end = input.find("\r\n", pos);

        int len = std::stoi(input.substr(pos, end - pos));

        pos = end + 2;

        result.push_back(input.substr(pos, len));

        pos += len + 2;
    }

    return result;
    
}
