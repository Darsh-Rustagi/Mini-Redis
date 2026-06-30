#include "storage/StorageEngine.hpp"

void StorageEngine::set(const std::string &key, const std::string &value) {
  database[key] = value;
}

std::optional<std::string> StorageEngine::get(const std::string &key) const {
  auto iterator = database.find(key);

  if (iterator == database.end()) {
    return std::nullopt;
  }

  return iterator->second;
}

bool StorageEngine::del(const std::string &key) {
  return database.erase(key) > 0;
}

bool StorageEngine::exists(const std::string &key) const {
  return database.find(key) != database.end();
}