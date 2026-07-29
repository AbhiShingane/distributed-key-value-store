#pragma once

#include<cstdint>
#include<mutex>
#include<queue>
#include<unordered_map>
#include<vector>

class NetworkMock
{
    private:
    static std::unordered_map<int, std::queue<std::vector<uint8_t>>> networkQueues;
    static std::mutex networkMutex;

    public:
    NetworkMock() = delete;
    ~NetworkMock() = delete;

    NetworkMock(const NetworkMock &other) = delete;
    NetworkMock& operator=(const NetworkMock &other) = delete;
    NetworkMock(const NetworkMock&& other) = delete;
    NetworkMock& operator=(const NetworkMock&& other) = delete;

    static void connect(int srcNode, int destNode);

    static void send(int destNode, const std::vector<uint8_t>& packet);

    static bool receive(int nodeId, std::vector<uint8_t> &packet);

    static size_t pendingPackets(int nodeId);

    static void clear();
};