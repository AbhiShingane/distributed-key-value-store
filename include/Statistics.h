#pragma once
#include<iostream>
#include<atomic>

class Statistics {
private:
    std::atomic<size_t> puts{0};
    std::atomic<size_t> gets{0};
    std::atomic<size_t> delets{0};
public:

    void recordPut();

    void recordGet();

    void recordDelete();

    size_t getPuts() const;

    size_t getGets() const;

    size_t getDeletes() const;
};