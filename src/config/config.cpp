#include "config/Config.hpp"

Config::Config() : port(6375) {}

int Config::getPort() const { return port; }

void Config::setPort(int value) { port = value; }