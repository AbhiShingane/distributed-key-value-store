#include<iostream>
#include<stdexcept>
#include<iomanip>
#include<cmath>

#include"Cluster.h"

#include "NetworkMock.h"
#include "Serializer.h"

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
    //Node &ownerNode = getOwnerNode(record.getKey());
    //std::cout<<"data sending for put: nodeid=  "<<ownerNode.id()<<std::endl;
    //return ownerNode.put(record);

    size_t ownerNode =
        partitioner.getNodeIndex(record.getKey());

    std::vector<uint8_t> packet =
        Serializer::serialize(record);

    NetworkMock::send(
        static_cast<int>(ownerNode),
        packet);
        
    return true;
    
}


std::optional<Record> Cluster::get(const std::string& key) const
{
    /*const Node &ownerNode = getOwnerNode(key);

    return ownerNode.get(key);*/
    size_t ownerNode =
        partitioner.getNodeIndex(key);
    
    return nodes[ownerNode]->get(key);    

}


bool Cluster::erase(const std::string& key)
{
    /*Node &ownerNode = getOwnerNode(key);

    return ownerNode.erase(key);*/

    size_t ownerNode =
        partitioner.getNodeIndex(key);
    
    return nodes[ownerNode]->erase(key);   
}


bool Cluster::contains(const std::string& key) const
{
    /*const Node &ownerNode = getOwnerNode(key);

    return ownerNode.contains(key);*/

    size_t ownerNode =
        partitioner.getNodeIndex(key);
    
    return nodes[ownerNode]->contains(key);
}

size_t Cluster::numberOfNodes() const
{
    return nodes.size();
}

/*Node& Cluster::getOwnerNode(const std::string& key)
{
    size_t nodeIndex = partitioner.getNodeIndex(key);
    return *(nodes[nodeIndex]);
}*/

/*const Node& Cluster::getOwnerNode(const std::string& key) const
{
    size_t nodeIndex = partitioner.getNodeIndex(key);
    return *(nodes[nodeIndex]);
}*/


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

void Cluster::processNetwork()
{
    std::vector<uint8_t> packet;
    
    try
    {
        for(auto& node: nodes)
        {
            while(NetworkMock::receive(node->id(), packet))
            {
                Record record = Serializer::deserialize(packet);

                node->put(record);
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return;
}


void Cluster::printOwnershipReport() const
{
    std::cout
        << "\n==================================================\n";
    std::cout
        << "              Ownership Report\n";
    std::cout
        << "==================================================\n";

    for (const auto& node : nodes)
    {
        std::cout
            << "\nNode "
            << node->id()
            << "\n--------------------------\n";

        auto keys =
            node->getStoredKeys();

        std::cout
            << "Owned Records : "
            << keys.size()
            << "\n\n";

        for (const auto& key : keys)
        {
            std::cout
                << key
                << '\n';
        }
    }
}

void Cluster::verifyOwnership() const
{
    std::cout
        << "\n==================================================\n";
    std::cout
        << "          Ownership Verification\n";
    std::cout
        << "==================================================\n";

    bool passed = true;

    for (const auto& node : nodes)
    {
        auto keys =
            node->getStoredKeys();

        for (const auto& key : keys)
        {
            auto expected =
                partitioner.getNodeIndex(key);

            bool ok =
                expected ==
                static_cast<size_t>(node->id());

            std::cout
                << std::left
                << std::setw(12)
                << key
                << " -> Expected Node "
                << expected
                << " | Actual Node "
                << node->id()
                << " : "
                << (ok ? "PASS" : "FAIL")
                << '\n';

            if (!ok)
            {
                passed = false;
            }
        }
    }

    std::cout
        << "\nVerification Result : "
        << (passed ? "PASS" : "FAIL")
        << "\n";

    return;
}

void Cluster::printLoadDistribution() const
{
    
    std::cout
        << "\n==================================================\n";
    std::cout
        << "              Load Distribution\n";
    std::cout
        << "==================================================\n";

    if (nodes.empty())
    {
        std::cout << "No nodes available.\n";
        return;
    }

    //----------------------------------------------------------
    // Calculate totals
    //----------------------------------------------------------
    size_t totalRecords = 0;

    for (const auto& node : nodes)
    {
        totalRecords += node->size();
    }

    double idealLoad =
        static_cast<double>(totalRecords) / nodes.size();

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Total Records      : "
              << totalRecords << '\n';

    std::cout << "Total Nodes        : "
              << nodes.size() << '\n';

    std::cout << "Ideal / Node       : "
              << idealLoad << "\n\n";

    //----------------------------------------------------------
    // Node wise distribution
    //----------------------------------------------------------
    size_t maxRecords = 0;
    size_t minRecords = SIZE_MAX;

    double totalDifference = 0.0;
    double maxDifference = 0.0;

    std::cout
        << std::left
        << std::setw(10) << "Node"
        << std::setw(12) << "Records"
        << std::setw(12) << "Ideal"
        << "Difference\n";

    std::cout
        << "-----------------------------------------------\n";

    for (const auto& node : nodes)
    {
        size_t records = node->size();

        maxRecords = std::max(maxRecords, records);
        minRecords = std::min(minRecords, records);

        double diff =
            static_cast<double>(records) - idealLoad;

        totalDifference += std::abs(diff);
        maxDifference =
            std::max(maxDifference, std::abs(diff));

        std::cout
            << std::left
            << std::setw(10)
            << node->id()

            << std::setw(12)
            << records

            << std::setw(12)
            << idealLoad;

        if (diff >= 0)
        {
            std::cout << "+" << diff;
        }
        else
        {
            std::cout << diff;
        }

        std::cout << '\n';
    }

    //----------------------------------------------------------
    // Overall metrics
    //----------------------------------------------------------
    double averageDifference =
        totalDifference / nodes.size();

    double imbalancePercent =
        totalRecords == 0
            ? 0.0
            : (totalDifference / totalRecords) * 100.0;

    //----------------------------------------------------------
    // Dynamic tolerance
    //
    // Allow approximately sqrt(ideal) records deviation.
    //----------------------------------------------------------
    double allowedDifference =
        std::ceil(std::sqrt(idealLoad) * 4);

    bool balanced =
        (maxDifference <= allowedDifference);

    //----------------------------------------------------------
    // Summary
    //----------------------------------------------------------
    std::cout
        << "\n-----------------------------------------------\n";

    std::cout
        << "Minimum Records      : "
        << minRecords << '\n';

    std::cout
        << "Maximum Records      : "
        << maxRecords << '\n';

    std::cout
        << "Record Difference    : "
        << (maxRecords - minRecords)
        << '\n';

    std::cout
        << "Max Difference       : "
        << maxDifference
        << " records\n";

    std::cout
        << "Average Difference   : "
        << averageDifference
        << " records\n";

    std::cout
        << "Overall Imbalance    : "
        << imbalancePercent
        << "%\n";

    std::cout
        << "Allowed Difference   : ±"
        << allowedDifference
        << " records\n";

    std::cout
        << "\nCluster Status       : "
        << (balanced ? "BALANCED" : "IMBALANCED")
        << '\n';

    std::cout
        << "==================================================\n";

    
    return;
}