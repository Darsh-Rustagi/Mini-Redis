#include "storage/StorageEngine.hpp"

void StorageEngine::set(const std::string &key, const std::string &value) {
  database.insert(key, value);
}

std::optional<std::string> StorageEngine::get(const std::string &key) const {
  return database.find(key);
}

bool StorageEngine::del(const std::string &key) {
  return database.erase(key);
}

bool StorageEngine::exists(const std::string &key) const {
  return database.contains(key);
}