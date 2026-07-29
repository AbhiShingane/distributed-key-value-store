#pragma once
#include<iostream>
#include<vector>
#include<sstream>
#include<string>

class Record {
private:
    std::string key;
    std::vector<std::string> values;

public:
    Record() = default;
    explicit Record(const std::string& k) : key(k){}

    Record(const std::string& k, const  std::vector<std::string>& val) : key(k), values(val) {}

    ~Record() = default;

     // Copy
    Record(const Record&) = default;
    Record& operator=(const Record&) = default;

    // Move
    Record(Record&&) noexcept = default;
    Record& operator=(Record&&) noexcept = default;

    const std::string& getKey() const {
        return key;
    }

    void setKey(const std::string& k)
    {
        key = k;
    }

    void addValue(const std::string& value)
    {
        values.push_back(value);
    }

    void setValues(const std::vector<std::string>& val)
    {
        values = val;
    }

    const std::vector<std::string>& getValues() const
    {
        return values;
    }

    const std::string& getValue(size_t index) const {
        if(index >= values.size())
        {
            throw std::out_of_range("Record value index out of range.");
        }

        return values[index];
    }


    size_t size() const
    {
        return values.size();
    }

    bool empty() const
    {
        return values.empty();
    }

    void clear()
    {
        key.clear();
        values.clear();
    }

};