#include<iostream>
#include"loader.h"
#include"Cluster.h"

#include<fstream>
#include<iostream>
#include<sstream>
#include<exception>
#include <stdexcept>

Loader::Loader(Cluster& cluster, const SchemaConfig& schemaConfig) : clusterobj(cluster), schemaConfig_(schemaConfig) {}


// Load a single record into the cluster
bool Loader::load(const std::string& key, const std::string& value) {

    if (!schemaConfig_.contains(key))
    {
        throw std::runtime_error(
            "Unknown schema field : " + key);
    }

    if (!schemaConfig_.validate(key, value))
    {
        throw std::runtime_error(
            "Invalid value '" + value +
            "' for field '" + value + "'");
    }

    Record record(key, value);
    clusterobj.put(record);
    return true;
}


// Load records from multiple files
bool Loader::loadFromFile(const std::vector<std::string>& fileNames) 
{
    bool success = true;

    try
    {
        for (const auto& fileName : fileNames) 
        {
            std::fstream file(fileName);
            if (!file.is_open()) {
                std::cerr << "Error: Could not open file " << fileName << std::endl;
                success = false;
                break;
            }

            std::string line;
            while (std::getline(file, line)) {
                if (!processline(line)) {
                    std::cerr << "Error: Failed to process line in file " << fileName << std::endl;
                    success = false;
                }
            }
        }

    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        success = false;
    }
    catch(...)
    {
        std::cerr << "Unknown exception occurred." << std::endl;
        success = false;
    }
        
    
    return success;
}

// Process a single line from the file and add it to the cluster
bool Loader::processline(const std::string& line) {
    
    if(line.empty())
    {
        return false;
    }


    std::stringstream ss(line);

    std::string key;
    std::string value;

    if(!std::getline(ss, key, ',') || !std::getline(ss, value)) {
        std::cerr << "Error: Invalid line format: " << line << std::endl;
        return false;
    }

    if (!schemaConfig_.contains(key))
    {
        throw std::runtime_error(
            "Unknown schema field : " + key);
    }

    if (!schemaConfig_.validate(key, value))
    {
        throw std::runtime_error(
            "Invalid value '" + value +
            "' for field '" + value + "'");
    }
    
    Record record(key, value);

    clusterobj.put(record);

    return true;
}
