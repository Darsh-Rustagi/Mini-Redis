#pragma once

#include "protocol/Command.hpp"
#include "storage/StorageEngine.hpp"

#include <string>

class CommandDispatcher {
public:
  CommandDispatcher();

  std::string dispatch(const Command &command);

private:
  StorageEngine storageEngine;
};