#pragma once

#include<iostream>

#include "SchemaConfig.h"

class ConfigParser
{
    public:

    ConfigParser() = default;
    ~ConfigParser() = default;

    bool parse(const std::string& filename);
    
    size_t getNumberOfNodes() const;

    const SchemaConfig& getSchemaConfig() const;

    private:
    void parseNodes(const std::string& line);
    void parseField(const std::string& line);
    static std::string trim(const std::string& str);
    
    size_t numberOfNodes{0};
    SchemaConfig schemaconfig;
};  