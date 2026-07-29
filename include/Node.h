#pragma once
#include <iostream>
#include "InMemoryKVstore.h"
#include "Statistics.h"
#include <optional>
#include "Record.h"
class Node
{
    private:
        int nodeId;
        InMemoryKVStore kvStore;
        mutable Statistics stats;

    public:
        explicit Node(int id);

        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;

        Node(Node&&) = delete;
        Node& operator=(Node&&) = delete;

        ~Node() = default;

        bool put(const Record& record);

        std::optional<Record> get(const std::string& key) const;

        bool erase(const std::string& key);

        bool contains(const std::string& key) const;

        size_t size() const;

        int id() const;

        void PrintStatistics() const;
};

