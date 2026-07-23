#include<iostream>
#include<stdexcept>
#include"Cluster.h"


Cluster::Cluster(size_t numNodes) : partitioner(numNodes) 
{
    
    try
    {
        nodes.reserve(numNodes);

        for (size_t i = 0; i < numNodes; ++i) {
            nodes.emplace_back(std::make_unique<Node>(static_cast<int>(i)));
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}


bool Cluster::put(const Record& record)
{
    Node &ownerNode = getOwnerNode(record.getKey());

    return ownerNode.put(record.getKey(), record.getValue());
}


std::optional<std::string> Cluster::get(const std::string& key) const
{
    const Node &ownerNode = getOwnerNode(key);

    return ownerNode.get(key);
}


bool Cluster::erase(const std::string& key)
{
    Node &ownerNode = getOwnerNode(key);

    return ownerNode.erase(key);
}


bool Cluster::contains(const std::string& key) const
{
    const Node &ownerNode = getOwnerNode(key);

    return ownerNode.contains(key);
}

size_t Cluster::numberOfNodes() const
{
    return nodes.size();
}

Node& Cluster::getOwnerNode(const std::string& key)
{
    size_t nodeIndex = partitioner.getNodeIndex(key);
    return *(nodes[nodeIndex]);
}

const Node& Cluster::getOwnerNode(const std::string& key) const
{
    size_t nodeIndex = partitioner.getNodeIndex(key);
    return *(nodes[nodeIndex]);
}


void Cluster::printStatistics() const
{
    std::cout << "\n========== Cluster Statistics ==========\n";

    size_t totalRecords = 0;

    for (const auto& node : nodes)
    {
        node->PrintStatistics();
        totalRecords += node->size();
    }

    std::cout << "\n========================================\n";
    std::cout << "Total Nodes   : " << nodes.size() << '\n';
    std::cout << "Total Records : " << totalRecords << '\n';
    std::cout << "========================================\n";
}