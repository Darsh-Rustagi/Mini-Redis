#pragma once

#include <optional>
#include <string>

#include "storage/HashTable.hpp"

class StorageEngine {
public:
  StorageEngine() = default;
  ~StorageEngine() = default;

  void set(const std::string &key, const std::string &value);

  std::optional<std::string> get(const std::string &key) const;

  bool del(const std::string &key);

  bool exists(const std::string &key) const;

private:
  HashTable database;
};