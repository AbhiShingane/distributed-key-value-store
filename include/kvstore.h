#ifndef KVSTORE_H
#define KVSTORE_H

#include <string>
#include <optional>
#include "Record.h"

class KVStore {
public:
    KVStore() = default;
    KVStore(const KVStore&) = delete;
    KVStore& operator=(const KVStore&) = delete;
    KVStore(KVStore&&) = delete;
    KVStore& operator=(KVStore&&) = delete;
    virtual ~KVStore() = default;

    virtual bool set(const Record& record) = 0;
    virtual std::optional<Record> get(const std::string& key) const = 0;
    virtual bool del(const std::string& key) = 0;
    virtual bool exists(const std::string& key) const = 0;
    virtual size_t size() const = 0;
};

#endif  // KVSTORE_H
