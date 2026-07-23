#ifndef INMEMORYKVSTORE_H
#define INMEMORYKVSTORE_H

#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <mutex>
#include <stdexcept>

#include "kvstore.h"

class InMemoryKVStore : public KVStore {
public:
    InMemoryKVStore() = default;
    InMemoryKVStore(const InMemoryKVStore&) = delete;
    InMemoryKVStore& operator=(const InMemoryKVStore&) = delete;
    InMemoryKVStore(InMemoryKVStore&&) = delete;
    InMemoryKVStore& operator=(InMemoryKVStore&&) = delete;
    ~InMemoryKVStore() override = default;

    bool set(const std::string& key, const std::string& value) override;
    std::string get(const std::string& key) const override;
    bool del(const std::string& key) override;
    bool exists(const std::string& key) const override;
    size_t size() const override;

private:
    std::unordered_map<std::string, std::string> store_;
    mutable std::shared_mutex mutex_;
};

#endif  // INMEMORYKVSTORE_H
