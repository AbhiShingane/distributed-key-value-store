#include<iostream>
#include "ConfigParser.h"

#include<fstream>
#include<sstream>
#include<stdexcept>

bool ConfigParser::parse(const std::string& filename)
{
    std::ifstream inputfile(filename);

    try
    {
        if(inputfile.is_open())
        {
            throw std::runtime_error("unable to open the configuration file: "+ filename);
        }

        std::string line;

        while(std::getline(inputfile, line))
        {
            if(line.empty())
                continue;

            if(line[0] == '#')
                continue;

            if(line.rFind("nodes=", 0) == 0)
            {
                parseNodes(line);
            }
            else if(line.rFind("field=", 0) == 0)
            {
                parseField(line);
            }
            else
            {
                throw std::runtime_error("Invalid config entry: "+ line);
            }
        }

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    if (numberOfNodes == 0)
    {
        throw std::runtime_error(
            "Cluster configuration missing 'nodes=' entry.");
    }

    return true;
     
}
    
void ConfigParser::parseNodes(const std::string& line)
{
    std::string value = line.substr(6);

    try
    {
        numberOfNodes = std::stoul(value);

        if (numberOfNodes_ == 0)
        {
            throw std::runtime_error(
                "Number of nodes must be greater than zero.");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }


   return; 
}

void ConfigParser::parseField(const std::string& line)
{
    std::string def = line.substr(6);

    std::stringstream ss(def);

    std::string fname;
    std::string ftype;
    
    try
    {
        if(!std::getline(ss, fname, ','))
        {
             throw std::runtime_error(
            "Invalid schema definition : " + line);
        }

        if (!std::getline(ss, ftype))
        {
            throw std::runtime_error(
                "Invalid schema definition : " + line);
        }


        Datatype type = DatatypeUtils::fromString(fname);

        if(!schemaconfig.addField(fname, ftype))
        {
            throw std::runtime_error(
                "Duplicate schema field : " + fieldName);
        }


    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
}

size_t ConfigParser::getNumberOfNodes() const
{
    return numberOfNodes;
}

const SchemaConfig& ConfigParser::getSchemaConfig() const
{
    return schemaConfig;
}
