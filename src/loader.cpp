#include<iostream>
#include"loader.h"
#include"Cluster.h"
#include "Datatype.h"

#include<fstream>
#include<iostream>
#include<sstream>
#include<exception>
#include <stdexcept>


Loader::Loader(Cluster& cluster, const SchemaConfig& schconfig) : clusterobj(cluster), schemaConfig(schconfig) {}


// Load a single record into the cluster
bool Loader::load(const Record& record) {

    clusterobj.put(record);
    //std::cout<<"In load function: "<<record.getKey()<<"  is added."<<std::endl;
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
            //std::cout<<"filename: "<<fileName<<std::endl; 
            std::fstream file(fileName);
            if (!file.is_open()) {
                std::cerr << "Error: Could not open file " << fileName << std::endl;
                success = false;
                break;
            }

            std::string line;
            while (std::getline(file, line)) {

                if(line.empty())
                {
                    continue;
                }

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
    
    try
    {
        Record record = parseRecord(line);
        //std::cout<<"Inside this Loader::processline() "<<std::endl;
        return load(record);
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return false;
    }
}

Record Loader::parseRecord(const std::string& line)
{
    std::stringstream ss(line);

    std::vector<std::string> columns;

    std::string token;

    while (std::getline(ss, token, ','))
    {
        columns.push_back(DataTypeUtils::trim(token));
    }

    const auto& fields = schemaConfig.getFields();

    /*for(const auto& field : fields)
    {
        std::cout
            << field.name
            << " -> "
            << DataTypeUtils::toString(field.type)
            << '\n';
    }*/

    if (columns.size() != fields.size())
    {
        throw std::runtime_error(
            "Column count mismatch. Expected " +
            std::to_string(fields.size()) +
            ", found " +
            std::to_string(columns.size()));
    }

    Record record;

    // First column is primary key
    if (columns[0].empty())
    {
        throw std::runtime_error(
            "Primary key cannot be empty.");
    }


    record.setKey(columns[0]);

    //std::cout << " \nIn Loader::parseRecord(const std::string& line) function Parsing Line : " << line << '\n';

    /*for(size_t i=0;i<columns.size();++i)
    {
        std::cout << "Column[" << i << "] = ["
                << columns[i] << "]\n";
    }*/
    // Validate every field
    for (size_t i = 0; i < fields.size(); ++i)
    {
        /*std::cout
            << "Validating "
            << fields[i].name
            << " value=["
            << columns[i]
            << "]\n";*/
        bool valid = 0;
        if (!DataTypeUtils::validate(fields[i].type,
                                     columns[i]))
        {
            valid = 0;
            throw std::runtime_error(
                "Invalid value '" +
                columns[i] +
                "' for field '" +
                fields[i].name + "'");

        }

        if(valid)
        {
            std::cout
            << "Result = "
            << valid
            << '\n';
        }

        // Skip key because it is already stored
        if (i != 0)
        {
            record.addValue(columns[i]);
        }
    }

    return record;
}
