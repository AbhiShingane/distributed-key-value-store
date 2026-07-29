#pragma once

#include<iostream>
#include<unordered_map>
#include<algorithm>
#include<string>
#include<vector>
#include "Datatype.h"

struct FieldDefinition
{
    std::string name;
    DataType type;
};

class SchemaConfig
{
    public:
    SchemaConfig() = default;
    ~SchemaConfig() = default;

    bool addField(const std::string& fieldName, DataType datatype);

    DataType getType(const std::string& fieldName) const;

    bool validate(const std::string& fieldName, const std::string& value) const;

    void printSchema() const;

    size_t size() const;

    bool contains(const std::string& fieldName) const;

    bool validateRecord(const std::vector<std::string>& val) const;

    const std::vector<FieldDefinition>& getFields() const;


    private:
    std::unordered_map<std::string, DataType> schema;
    std::vector<FieldDefinition> fields;
};