#pragma once

#include <optional>
#include <string>
#include <unordered_map>

class StorageEngine {
public:
  StorageEngine() = default;
  ~StorageEngine() = default;

  // Insert or update a key
  void set(const std::string &key, const std::string &value);

  // Return the value if it exists
  std::optional<std::string> get(const std::string &key) const;

  // Delete a key
  bool del(const std::string &key);

  // Check if key exists
  bool exists(const std::string &key) const;

private:
  std::unordered_map<std::string, std::string> database;
};