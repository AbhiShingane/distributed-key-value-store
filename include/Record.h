#pragma once
#include<iostream>

class Record {
private:
    std::string key;
    std::string value;

public:
    Record(const std::string& k, const std::string& v) : key(k), value(v) {}

    const std::string& getKey() const {
        return key;
    }

    const std::string& getValue() const {
        return value;
    }
};