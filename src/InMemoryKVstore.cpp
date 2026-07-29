#include "InMemoryKVstore.h"
#include <stdexcept>
#include <iostream>

bool InMemoryKVStore::set(const Record& record) {
    bool success = false;
    std::unique_lock<std::shared_mutex> lock(mutex_);
    try {
        store_[record.getKey()] = record;
        std::cout<<"record added: "<<record.getKey()<<std::endl;
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