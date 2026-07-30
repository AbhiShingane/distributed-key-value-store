#include "InMemoryKVstore.h"
#include "Logger.h"
#include <stdexcept>
#include <iostream>

bool InMemoryKVStore::set(const Record& record) {
    bool success = false;
    std::unique_lock<std::shared_mutex> lock(mutex_);
    try {
        if(store_.find(record.getKey()) != store_.end())
        {
            Logger::debug(
                record.getKey() +
                " : record is already available");

            return true;
        }

        store_[record.getKey()] = record;
        Logger::debug(
                record.getKey() +
                " : record added");
        success = true;
    } catch (const std::bad_alloc&) {
        success = false;
        throw std::runtime_error("Memory allocation failed");
    }

    return success;
    
}

std::optional<Record> InMemoryKVStore::get(const std::string& key) const{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    auto it = store_.find(key);
    if (it != store_.end()) {
        return it->second;
    }

    
}

bool InMemoryKVStore::del(const std::string& key) {
    bool success = false;
    std::unique_lock<std::shared_mutex> lock(mutex_);
    try
    {
        if (store_.find(key) == store_.end()) {
            success = false;
            throw std::runtime_error("Key not found");
        }
        store_.erase(key);
        success = true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return success;
}

bool InMemoryKVStore::exists(const std::string& key) const {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return store_.find(key) != store_.end();
}

size_t InMemoryKVStore::size() const {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return store_.size();
}

std::vector<std::string> InMemoryKVStore::getAllKeys() const
{
    std::shared_lock lock(mutex_);

    std::vector<std::string> keys;

    keys.reserve(store_.size());

    for(const auto& entry: store_)
    {
        keys.push_back(entry.first);
    }

    return keys;
}

std::vector<Record> InMemoryKVStore::getAllRecords() const
{
    std::shared_lock lock(mutex_);

    std::vector<Record> records;

    records.reserve(store_.size());

    for(const auto& entry: store_)
    {
        records.push_back(entry.second);
    }


    return records;
}