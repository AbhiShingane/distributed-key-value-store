#include <iostream>
#include "Node.h"


Node::Node(int id) : nodeId(id) {}

bool Node::put(const std::string& key, const std::string& value) {
    stats.recordPut();
    return kvStore.set(key, value);
}


std::optional<std::string> Node::get(const std::string& key) const {
    std::optional<std::string> value;
    stats.recordGet();
    try {
        value = kvStore.get(key);
    } catch (const std::runtime_error&) {
        //return std::nullopt;
    }

    return value;
}


bool Node::erase(const std::string& key) {
    stats.recordDelete();
    return kvStore.del(key);
}

bool Node::contains(const std::string& key) const {
    return kvStore.exists(key);
}

size_t Node::size() const {
    return kvStore.size();
}

int Node::id() const {
    return nodeId;
}

void Node::PrintStatistics() const {
    std::cout << "Node ID: " << nodeId << std::endl;
    std::cout << "Records: " << size() << std::endl;
    std::cout << "Puts: " << stats.getPuts() << std::endl;
    std::cout << "Gets: " << stats.getGets() << std::endl;
    std::cout << "Deletes: " << stats.getDeletes() << std::endl;
    std::cout << "-----------------------------" << std::endl;
}