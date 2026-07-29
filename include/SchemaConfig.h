#pragma once

#include<iostream>
#include<unordered_map>
#include<algorithm>
#include<string>
#include"Datatype.h"


class SchemaConfig
{
    public:
    SchemaConfig() = default;
    ~SchemaConfig() = default;

    bool addField(const std::string& fieldName, Datatype datatype);

    Datatype getType(const std::string& fieldName) const;

    bool validate(const std::string& fieldName, const std::string& value) const;

    void printSchema() const;

    size_t size() const;

    bool contains(const std::string& fieldName) const;

    private:
    unorderd_map<std::string, Datatype> schema;
};