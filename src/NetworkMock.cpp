#include<iostream>
#include "NetworkMock.h"

std::unordered_map<
    int,
    std::queue<std::vector<uint8_t>>> NetworkMock::networkQueues;

std::mutex NetworkMock::networkMutex;

size_t NetworkMock::packetsSent = 0;
size_t NetworkMock::packetsReceived = 0;

void NetworkMock::connect(int srcNode, int destNode)
{
    std::lock_guard<std::mutex> lock(networkMutex);

    networkQueues[srcNode];
    networkQueues[destNode];

    /*std::cout
        << "Network connected : "
        << srcNode
        << " -> "
        << destNode
        << std::endl;*/
}

void NetworkMock::send(int destNode, const std::vector<uint8_t>& packet)
{
    std::lock_guard<std::mutex> lock(networkMutex);

    networkQueues[destNode].push(packet);

    /*std::cout
        << "[Network] Packet sent to Node "
        << destNode
        << " ("
        << packet.size()
        << " bytes)"
        << std::endl;*/
    
   ++packetsSent;     

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

    ++packetsReceived;

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

    packetsSent = 0;
    packetsReceived = 0;
}

void NetworkMock::printStatistics()
{
    std::lock_guard<std::mutex> lock(networkMutex);

    size_t pendingPackets = 0;

    for (const auto& entry : networkQueues)
    {
        pendingPackets += entry.second.size();
    }

    std::cout
        << "\n==================================================\n";
    std::cout
        << "              Network Statistics\n";
    std::cout
        << "==================================================\n";

    std::cout << "Packets Sent      : "
              << packetsSent << '\n';

    std::cout << "Packets Received  : "
              << packetsReceived << '\n';

    std::cout << "Packets Pending   : "
              << pendingPackets << '\n';

    std::cout << "Active Queues     : "
              << networkQueues.size() << '\n';

    std::cout << "Network Status    : "
              << (pendingPackets == 0 ? "HEALTHY" : "PENDING")
              << '\n';

    std::cout
        << "==================================================\n";
}