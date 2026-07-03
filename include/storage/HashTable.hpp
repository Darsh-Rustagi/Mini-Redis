#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

class HashTable {
public:
  HashTable() : buckets_(16), num_elements_(0) {}

  void insert(const std::string &key, const std::string &value) {
    if (should_rehash()) {
      rehash(buckets_.size() * 2);
    }

    size_t first_deleted = static_cast<size_t>(-1);
    size_t index = probe_start(key);

    for (size_t i = 0; i < buckets_.size(); ++i) {
      size_t idx = (index + i) & (buckets_.size() - 1);
      Bucket &bucket = buckets_[idx];

      if (bucket.state == State::EMPTY) {
        size_t target = (first_deleted != static_cast<size_t>(-1)) ? first_deleted : idx;
        buckets_[target].state = State::OCCUPIED;
        buckets_[target].key = key;
        buckets_[target].value = value;
        ++num_elements_;
        return;
      }

      if (bucket.state == State::DELETED) {
        if (first_deleted == static_cast<size_t>(-1)) {
          first_deleted = idx;
        }
        continue;
      }

      if (bucket.state == State::OCCUPIED && bucket.key == key) {
        bucket.value = value;
        return;
      }
    }

    rehash(buckets_.size() * 2);
    insert(key, value);
  }

  std::optional<std::string> find(const std::string &key) const {
    size_t index = probe_start(key);

    for (size_t i = 0; i < buckets_.size(); ++i) {
      size_t idx = (index + i) & (buckets_.size() - 1);
      const Bucket &bucket = buckets_[idx];

      if (bucket.state == State::EMPTY) {
        return std::nullopt;
      }

      if (bucket.state == State::OCCUPIED && bucket.key == key) {
        return bucket.value;
      }
    }

    return std::nullopt;
  }

  bool erase(const std::string &key) {
    size_t index = probe_start(key);

    for (size_t i = 0; i < buckets_.size(); ++i) {
      size_t idx = (index + i) & (buckets_.size() - 1);
      Bucket &bucket = buckets_[idx];

      if (bucket.state == State::EMPTY) {
        return false;
      }

      if (bucket.state == State::OCCUPIED && bucket.key == key) {
        bucket.state = State::DELETED;
        --num_elements_;
        return true;
      }
    }

    return false;
  }

  bool contains(const std::string &key) const {
    return find(key).has_value();
  }

  size_t size() const { return num_elements_; }

private:
  enum class State { EMPTY, OCCUPIED, DELETED };

  struct Bucket {
    State state = State::EMPTY;
    std::string key;
    std::string value;
  };

  std::vector<Bucket> buckets_;
  size_t num_elements_;

  static uint64_t rolling_hash(const std::string &key) {
    uint64_t hash = 0;
    for (unsigned char c : key) {
      hash = hash * 131 + c;
    }
    return hash;
  }

  size_t probe_start(const std::string &key) const {
    return rolling_hash(key) & (buckets_.size() - 1);
  }

  bool should_rehash() const {
    return num_elements_ >= buckets_.size() * 3 / 4;
  }

  void rehash(size_t new_capacity) {
    std::vector<Bucket> old_buckets;
    old_buckets.swap(buckets_);
    buckets_.resize(new_capacity);
    num_elements_ = 0;

    for (const auto &bucket : old_buckets) {
      if (bucket.state == State::OCCUPIED) {
        insert(bucket.key, bucket.value);
      }
    }
  }
};
