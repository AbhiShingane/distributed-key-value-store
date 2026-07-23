#pragma once

#include <cstddef>
#include <string>

class Partitioner
{
public:
    explicit Partitioner(size_t totalNodes);

    size_t getNodeIndex(const std::string& key) const;

    size_t totalNodes() const;

private:
    size_t totalNodes_;
};