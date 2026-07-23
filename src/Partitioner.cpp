#include "Partitioner.h"

#include <functional>
#include <stdexcept>


// Constructor for the Partitioner class. Initializes the total number of nodes in the cluster.

Partitioner::Partitioner(size_t totalNodes)
    : totalNodes_(totalNodes)
{
    if (totalNodes_ == 0)
    {
        throw std::invalid_argument(
            "Cluster must contain at least one node.");
    }
}

// Returns the index of the node that owns the given key. The index is determined by hashing the key and taking the modulus with the total number of nodes.
size_t Partitioner::getNodeIndex(const std::string& key) const
{
    std::hash<std::string> hasher;

    return hasher(key) % totalNodes_;
}

size_t Partitioner::totalNodes() const
{
    return totalNodes_;
}