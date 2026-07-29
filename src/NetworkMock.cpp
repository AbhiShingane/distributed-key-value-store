#include<iostream>
#include "NetworkMock.h"

std::unordered_map<
    int,
    std::queue<std::vector<uint8_t>>> NetworkMock::networkQueues;

std::mutex NetworkMock::networkMutex;

void NetworkMock::connect(int srcNode, int destNode)
{
    std::lock_guard<std::mutex> lock(networkMutex);

    networkQueues[srcNode];
    networkQueues[destNode];

    std::cout
        << "Network connected : "
        << srcNode
        << " -> "
        << destNode
        << std::endl;
}

void NetworkMock::send(int destNode, const std::vector<uint8_t>& packet)
{
    std::lock_guard<std::mutex> lock(networkMutex);

    networkQueues[destNode].push(packet);

    std::cout
        << "[Network] Packet sent to Node "
        << destNode
        << " ("
        << packet.size()
        << " bytes)"
        << std::endl;

}

bool NetworkMock::receive(int nodeId, std::vector<uint8_t> &packet)
{
    std::lock_guard<std::mutex> lock(networkMutex);

    auto itr = networkQueues.find(nodeId);

    if(itr == networkQueues.end())
    {
        return false;
    }

    if(itr->second.empty())
    {
        return false;
    }

    packet = std::move(itr->second.front());

    itr->second.pop();

    return true;
}

size_t NetworkMock::pendingPackets(int nodeId)
{
    std::lock_guard<std::mutex> lock(networkMutex);

    auto itr = networkQueues.find(nodeId);

    if (itr == networkQueues.end())
    {
        return 0;
    }

    return itr->second.size();
}

void NetworkMock::clear()
{
    std::lock_guard<std::mutex> lock(networkMutex);

    networkQueues.clear();
}